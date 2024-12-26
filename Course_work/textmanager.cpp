#include "textmanager.h"
#include "database.h"
#include "settingsdialog.h"

TextManager::TextManager(QWidget *parent, int user_id, QString name) : QWidget(parent), q_user_id(user_id), q_name(name)
{
    QPushButton *settingsButton = new QPushButton("Настройки", this);

    QLabel *label = new QLabel("Привет, " + q_name, this);

    QSplitter *splitter = new QSplitter(this);

    // Левая панель
    QWidget *leftWidget = new QWidget;
    leftWidget->setMinimumWidth(150);
    leftWidget->setMaximumWidth(300);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);

    pageList = new QListWidget(this);

    connect(pageList, &QListWidget::currentRowChanged, this, &TextManager::switchPage);

    pageList->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(pageList, &QListWidget::customContextMenuRequested, this, &TextManager::showContextMenu);
    connect(settingsButton, &QPushButton::clicked, this, &TextManager::openSettings);

    leftLayout->addWidget(label);
    leftLayout->addWidget(settingsButton); // Добавляем кнопку в компоновку
    leftLayout->addWidget(createButtonWithIcon(":icons/AddDoc.svg", &TextManager::addPage));
    leftLayout->addWidget(createButtonWithIcon(":icons/DelDoc.svg", &TextManager::deletePage));
    leftLayout->addWidget(pageList);
    leftLayout->addStretch();

    splitter->addWidget(leftWidget);

    // Правая панель
    textStack = new QStackedWidget(this);
    splitter->addWidget(textStack);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(splitter);
    setLayout(mainLayout);

    toolbar = nullptr;  // Инициализируем toolbar как nullptr

    loadPagesFromDatabase();

}

void TextManager::addPage()
{
    QTextEdit *edit = new QTextEdit(this);
    // Получаем доступ к объекту QTextDocument, который связан с QTextEdit
    QTextDocument *doc = edit->document();

    // Устанавливаем отступы для документа
    doc->setDocumentMargin(25);

    textStack->addWidget(edit);
    pageList->addItem(QString("Page %1").arg(textStack->count()));
    pageList->setCurrentRow(textStack->count() - 1);

    savePageToDatabase(textStack->count() - 1);

    // Подключаем обработчик изменения курсора
    connect(edit, &QTextEdit::cursorPositionChanged, this, &TextManager::handleCursorChange);

    // Если тулбар еще не создан, создаем его для текущей страницы
    if (!toolbar && textStack->count() > 0) {
        QTextEdit *firstTextEdit = qobject_cast<QTextEdit *>(textStack->widget(0));
        if (firstTextEdit) {
            toolbar = new ToolBar(firstTextEdit, this);  // Передаем первый QTextEdit
            toolbar->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
            toolbar->hide();  // Сначала скрыть ToolBar
        }
    }

}


void TextManager::handleCursorChange()
{
    QTextEdit *currentTextEdit = qobject_cast<QTextEdit *>(textStack->currentWidget());
    if (!currentTextEdit) return;

    QTextCursor cursor = currentTextEdit->textCursor();
    if (!cursor.hasSelection()) {
        // Если нет выделения, скрываем ToolBar
        if (toolbar) {
            toolbar->hide();
        }
        return;
    }

    // Если есть выделение, показываем ToolBar
    QRect rect = currentTextEdit->cursorRect(cursor);

    // Позиционируем ToolBar чуть выше выделения
    if (toolbar) {
        // Вычисляем координаты для тулбара
        QPoint toolbarPos = rect.topLeft() + QPoint(0, -toolbar->height() + 175);  // Отступ сверху

        // Перемещаем тулбар в нужную позицию
        toolbar->move(currentTextEdit->mapToGlobal(toolbarPos));
        toolbar->show();
        toolbar->raise();  // Поднимаем ToolBar поверх других виджетов
    }

    // Дополнительная проверка, чтобы убедиться, что ToolBar не перекрывается другими виджетами
    QWidget *topLevelWidget = toolbar->topLevelWidget();
    if (topLevelWidget) {
        topLevelWidget->raise();  // Поднимаем родительское окно если оно есть
    }
}

void TextManager::deletePage()
{
    int index = pageList->currentRow();  // Получаем текущий выбранный индекс
    if (index < 0 || index >= pageInfoList.size()) {
        qDebug() << "Invalid page index:" << index;
        return;  // Если индекс невалиден, ничего не делаем
    }

    // Получаем виджет, который отображает содержимое страницы
    QWidget *widget = textStack->widget(index);
    QTextEdit *edit = qobject_cast<QTextEdit *>(widget);  // Преобразуем в QTextEdit
    if (!edit) {
        qDebug() << "Failed to cast widget at index" << index << "to QTextEdit";
        return;  // Если не удалось преобразовать в QTextEdit, ничего не делаем
    }

    // Удаляем страницу из базы данных и из локальной структуры данных
    if (!deletePageFromDatabase(index)) {
        qDebug() << "Error: Failed to delete page from database";
        return;
    }

    // Удаляем элемент из UI
    pageList->takeItem(index);  // Удаляем элемент из списка
    textStack->removeWidget(edit);  // Удаляем виджет из стека
    delete edit;  // Удаляем сам виджет
    qDebug() << "Deleted QTextEdit widget at index" << index;

    // После удаления страницы обновляем индексы, если это необходимо
    // Обновляем индексы в UI и структуре
    if (textStack->count() == 0 && toolbar) {
        toolbar->hide();
    }

    // Логируем состояние после удаления
    qDebug() << "Current pageInfoList size after deletion:" << pageInfoList.size();
    qDebug() << "Current pageList count after deletion:" << pageList->count();
    qDebug() << "Current textStack count after deletion:" << textStack->count();
}

void TextManager::switchPage(int index)
{
    if (index >= 0 && index < textStack->count())
    {
        textStack->setCurrentIndex(index);

        // Обновляем тулбар для новой текущей страницы
        QTextEdit *currentTextEdit = qobject_cast<QTextEdit *>(textStack->currentWidget());
        if (currentTextEdit && toolbar) {
            toolbar->setTextEdit(currentTextEdit);  // Обновляем QTextEdit в тулбаре
        }
    }
}

void TextManager::showContextMenu(const QPoint &pos)
{
    QModelIndex index = pageList->indexAt(pos);
    if (index.isValid())
    {
        QMenu contextMenu;
        QAction *renameAction = contextMenu.addAction("Rename");

        // Обработка выбора действия в меню
        connect(renameAction, &QAction::triggered, this, [this, index]() {
            renamePage(index.row());
        });

        contextMenu.exec(pageList->mapToGlobal(pos));
    }
}

void TextManager::renamePage(int index)
{
    QString currentName = pageList->item(index)->text();
    bool ok;
    QString newName = QInputDialog::getText(this, "Rename Page", "Enter new name:", QLineEdit::Normal, currentName, &ok);

    if (ok && !newName.isEmpty())
    {
        // Обновляем заголовок в списке
        pageList->item(index)->setText(newName);

        // Обновляем информацию о странице в локальной структуре
        pageInfoList[index].title = newName;

        // Обновляем заголовок в базе данных
        QSqlQuery query;
        query.prepare("UPDATE documents SET title = :title WHERE document_id = :document_id");
        query.bindValue(":title", newName);
        query.bindValue(":document_id", pageInfoList[index].document_id);

        if (!query.exec()) {
            qDebug() << "Error updating title in database: " << query.lastError().text();
        }
    }
}

void TextManager::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_F2)  // Проверяем, была ли нажата клавиша F2
    {
        int index = pageList->currentRow();  // Получаем текущий выбранный элемент
        if (index >= 0)  // Если элемент выбран
        {
            renamePage(index);  // Вызываем метод переименования
        }
    }
    else
    {
        QWidget::keyPressEvent(event);  // Обрабатываем другие клавиши
    }
}


void TextManager::savePagesToXml(const QString &filePath)
{
    QDomDocument doc;
    QDomElement root = doc.createElement("Pages"); // Корневой элемент
    doc.appendChild(root);

    // Сохраняем каждую страницу
    for (int i = 0; i < textStack->count(); ++i)
    {
        QTextEdit *edit = qobject_cast<QTextEdit *>(textStack->widget(i));

        // Создаем элемент для каждой страницы
        QDomElement page = doc.createElement("Page");
        page.setAttribute("index", i); // Атрибут для идентификации страницы

        // Вставляем HTML-содержимое в CDATA-секцию
        QDomCDATASection pageContent = doc.createCDATASection(edit->toHtml());
        page.appendChild(pageContent);

        root.appendChild(page); // Добавляем страницу в корневой элемент
    }

    // Сохраняем XML в файл
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << doc.toString(); // Записываем весь XML-контент
        file.close();
    }
}

void TextManager::loadPagesFromXml(const QString &filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QDomDocument doc;
        if (doc.setContent(&file))
        {
            QDomElement root = doc.documentElement(); // Получаем корневой элемент
            QDomNodeList pages = root.elementsByTagName("Page"); // Получаем все элементы <Page>

            for (int i = 0; i < pages.size(); ++i)
            {
                QDomNode pageNode = pages.at(i);
                if (pageNode.isElement())
                {
                    QDomElement pageElement = pageNode.toElement();
                    QString pageHtml = pageElement.firstChild().nodeValue(); // Получаем HTML из CDATA

                    QTextEdit *edit = new QTextEdit(this); // Создаем новый QTextEdit
                    edit->setHtml(pageHtml); // Загружаем HTML в QTextEdit
                    textStack->addWidget(edit); // Добавляем в стек
                    pageList->addItem(QString("Page %1").arg(i + 1)); // Добавляем элемент в список страниц
                }
            }
        }
        file.close();
    }
}

void TextManager::onTextChanged()
{
    QTextEdit *currentTextEdit = qobject_cast<QTextEdit *>(textStack->currentWidget());
    if (!currentTextEdit) return;

    QTextCursor cursor = currentTextEdit->textCursor();
    QTextBlock block = cursor.block();

    QString blockText = block.text();  // Получаем текст текущего блока

    // Проверяем, начинается ли строка с цифры и точки (для нумерованного списка)
    QRegularExpression numberListRegex("^\\d+\\.\\s");
    if (numberListRegex.match(blockText).hasMatch()) {
        QTextListFormat listFormat;
        listFormat.setStyle(QTextListFormat::ListDecimal);  // Нумерованный список
        cursor.beginEditBlock();
        if (!cursor.currentList()) {
            cursor.createList(listFormat);
        }
        cursor.endEditBlock();
    }
    // Проверяем, начинается ли строка с дефиса или звездочки (для маркированного списка)
    QRegularExpression bulletListRegex("^[\\-\\*]\\s");
    if (bulletListRegex.match(blockText).hasMatch()) {
        QTextListFormat listFormat;
        listFormat.setStyle(QTextListFormat::ListDisc);  // Маркированный список
        cursor.beginEditBlock();
        if (!cursor.currentList()) {
            cursor.createList(listFormat);
        }
        cursor.endEditBlock();
    }
}


bool TextManager::savePageToDatabase(int pageIndex)
{
    QTextEdit *edit = qobject_cast<QTextEdit *>(textStack->widget(pageIndex));
    if (!edit) return false;

    QString title = pageList->item(pageIndex)->text();
    QString content = edit->toHtml();  // Сохраняем HTML содержимое

    // Если страница уже существует в базе данных (имеет document_id)
    if (pageIndex < pageInfoList.size()) {
        int document_id = pageInfoList[pageIndex].document_id;

        QSqlQuery query;
        query.prepare("UPDATE documents SET title = :title, content = :content WHERE document_id = :document_id");
        query.bindValue(":title", title);
        query.bindValue(":content", content);
        query.bindValue(":document_id", document_id);

        if (!query.exec()) {
            qDebug() << "Error updating page to database: " << query.lastError().text();
            return false;
        }

        // Обновляем информацию в локальной структуре
        pageInfoList[pageIndex].title = title;
        pageInfoList[pageIndex].content = content;
    }
    else {
        // Если страница новая, то вставляем её в базу данных
        QSqlQuery query;
        query.prepare("INSERT INTO documents (user_id, title, content) VALUES (:user_id, :title, :content)");
        query.bindValue(":user_id", q_user_id);
        query.bindValue(":title", title);
        query.bindValue(":content", content);

        if (!query.exec()) {
            qDebug() << "Error saving new page to database: " << query.lastError().text();
            return false;
        }

        // Получаем document_id для новой страницы
        int document_id = query.lastInsertId().toInt();

        // Добавляем новую страницу в локальный список
        PageInfo pageInfo = { document_id, title, content };
        pageInfoList.append(pageInfo);
    }

    return true;
}


void TextManager::updatePagesInDatabase()
{
    // Пройдем по всем страницам в стеке
    for (int i = 0; i < textStack->count(); ++i)
    {
        QTextEdit *edit = qobject_cast<QTextEdit *>(textStack->widget(i));
        if (!edit) continue;

        QString title = pageList->item(i)->text();  // Заголовок страницы из списка
        QString content = edit->toHtml();  // HTML содержимое страницы

        if (content.isEmpty()) {
            qDebug() << "Content is empty for page: " << title;
            continue;  // Если контент пустой, пропускаем страницу
        }

        // Проверим, существует ли страница в базе данных
        QSqlQuery query;
        query.prepare("SELECT document_id FROM documents WHERE user_id = :user_id AND title = :title");
        query.bindValue(":user_id", q_user_id);  // Используем текущий user_id
        query.bindValue(":title", title);  // Заголовок страницы

        if (query.exec()) {
            if (query.next()) {
                // Если запись найдена, обновляем содержимое
                int document_id = query.value(0).toInt();
                QSqlQuery updateQuery;
                updateQuery.prepare("UPDATE documents SET content = :content, title = :title, updated_at = CURRENT_TIMESTAMP WHERE document_id = :document_id");
                updateQuery.bindValue(":title", title);
                updateQuery.bindValue(":content", content);
                updateQuery.bindValue(":document_id", document_id);

                if (!updateQuery.exec()) {
                    qDebug() << "Error updating document: " << updateQuery.lastError().text();
                } else {
                    qDebug() << "Document updated in database with id: " << document_id;
                }
            }
            else {
                // Если записи нет, добавляем новую
                QSqlQuery insertQuery;
                insertQuery.prepare("INSERT INTO documents (user_id, title, content) VALUES (:user_id, :title, :content)");
                insertQuery.bindValue(":user_id", q_user_id);
                insertQuery.bindValue(":title", title);
                insertQuery.bindValue(":content", content);

                if (!insertQuery.exec()) {
                    qDebug() << "Error inserting new document: " << insertQuery.lastError().text();
                } else {
                    qDebug() << "New document inserted with title: " << title;
                }
            }
        } else {
            qDebug() << "Error querying database for document: " << query.lastError().text();
        }
    }
}



bool TextManager::deletePageFromDatabase(int pageIndex)
{
    if (pageIndex < 0 || pageIndex >= pageInfoList.size()) {
        qDebug() << "Invalid page index:" << pageIndex;
        return false;
    }

    // Получаем виджет, который отображает содержимое страницы
    QTextEdit *edit = qobject_cast<QTextEdit *>(textStack->widget(pageIndex));
    if (!edit) {
        qDebug() << "Failed to cast widget at index" << pageIndex << "to QTextEdit";
        return false;
    }

    // Получаем document_id страницы
    int document_id = pageInfoList[pageIndex].document_id;

    // Убедимся, что document_id валиден
    if (document_id == -1) {
        qDebug() << "Invalid document_id for page index" << pageIndex;
        return false;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM documents WHERE document_id = :document_id");
    query.bindValue(":document_id", document_id);

    if (!query.exec()) {
        qDebug() << "Error deleting page from database (ID: " << document_id << "):" << query.lastError().text();
        return false;
    }

    qDebug() << "Page deleted from database, document_id:" << document_id;

    // Удаляем страницу из локальной структуры
    pageInfoList.removeAt(pageIndex);
    qDebug() << "Removed page from pageInfoList at index" << pageIndex;

    return true;
}

bool TextManager::loadPagesFromDatabase()
{
    QSqlQuery query;
    query.prepare("SELECT document_id, title, content FROM documents WHERE user_id = :user_id");
    query.bindValue(":user_id", q_user_id);

    if (!query.exec()) {
        qDebug() << "Error loading pages from database: " << query.lastError().text();
        return false;
    }

    pageInfoList.clear();


    while (query.next()) {
        int document_id = query.value(0).toInt();
        QString title = query.value(1).toString();
        QString content = query.value(2).toString();

        addPageFromDb(title,content);

        // Сохраняем информацию о странице
        PageInfo pageInfo = { document_id, title, content };
        pageInfoList.append(pageInfo);
    }

    return true;
}


void TextManager::addPageFromDb(QString& title,QString& content)
{
    QTextEdit *edit = new QTextEdit(this);
    edit->setHtml(content);
    textStack->addWidget(edit);
    pageList->addItem(title);

    // Подключаем обработчик изменения курсора
    connect(edit, &QTextEdit::cursorPositionChanged, this, &TextManager::handleCursorChange);

    // Если тулбар еще не создан, создаем его для текущей страницы
    if (!toolbar && textStack->count() > 0) {
        QTextEdit *firstTextEdit = qobject_cast<QTextEdit *>(textStack->widget(0));
        if (firstTextEdit) {
            toolbar = new ToolBar(firstTextEdit, this);  // Передаем первый QTextEdit
            toolbar->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
            toolbar->hide();  // Сначала скрыть ToolBar
        }
    }

}



QPushButton* TextManager::createButtonWithIcon(const QString &iconPath, void (TextManager::*slot)())
{
    QPushButton *button = new QPushButton();
    QIcon icon(iconPath);  // Загружаем иконку
    button->setIcon(icon);  // Устанавливаем иконку
    button->setIconSize(QSize(20, 20));
    button->setFixedSize(100, 40);
    connect(button, &QPushButton::clicked, this, slot);  // Привязываем слот
    return button;
}



void TextManager::openSettings()
    {
        SettingsDialog *settingsDialog = new SettingsDialog(this);
        connect(settingsDialog, &SettingsDialog::themeChanged, this, &TextManager::applyTheme);
        settingsDialog->exec();
    }

void TextManager:: applyTheme(const QString &theme)
    {
           QString qssFileName = theme == "dark" ? "testDark.qss" : "testLight.qss";
           QString pathToFile = ":style/style/" + qssFileName;
           QFile file(pathToFile);

           if (file.open(QFile::ReadOnly))
           {
               QString styleSheet = QTextStream(&file).readAll();
               setStyleSheet(styleSheet);
               file.close();
           }
           if (!file.open(QFile::ReadOnly)) {
              qDebug() << "Не удалось открыть файл стилей:" << file.errorString();

           }
    }

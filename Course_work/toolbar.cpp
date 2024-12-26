#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QFontDialog>
#include <QColorDialog>
#include <QInputDialog>
#include <QScrollArea>
#include <QLabel>

class ToolBar : public QWidget
{
    Q_OBJECT

public:
    ToolBar(QTextEdit *textEdit, QWidget *parent = nullptr) : QWidget(parent), textEdit(textEdit)
    {
        setFixedHeight(120);  // Устанавливаем фиксированную высоту панели инструментов

            // Главный макет
            QVBoxLayout *mainLayout = new QVBoxLayout(this);

            // Прокручиваемая область
            QScrollArea *scrollArea = new QScrollArea(this);
            scrollArea->setWidgetResizable(true);  // Делаем область прокручиваемой по мере необходимости
            QWidget *toolBarWidget = new QWidget(scrollArea);  // Это будет виджет, который будет прокручиваться

            QVBoxLayout *toolBarLayout = new QVBoxLayout(toolBarWidget);  // Макет для панели инструментов

            // Макет с кнопками для форматирования текста
            QHBoxLayout *layout1 = new QHBoxLayout();
            layout1->addWidget(createButtonWithIcon(":icons/font.svg", &ToolBar::changeFont));
            layout1->addWidget(createButtonWithIcon(":icons/bold.svg", &ToolBar::toggleBold));
            layout1->addWidget(createButtonWithIcon(":icons/italic.svg", &ToolBar::toggleItalic));
            layout1->addWidget(createButtonWithIcon(":icons/underline.svg", &ToolBar::toggleUnderline));
            layout1->addWidget(createButtonWithIcon(":icons/color.svg", &ToolBar::changeColor));
            layout1->addWidget(createButtonWithIcon(":icons/highlighter-solid.svg", &ToolBar::changeBgColor));

            // Выбор шрифта
            QComboBox *fontSizeBox = new QComboBox(this);
            for (int i = 8; i <= 48; i += 2)
                fontSizeBox->addItem(QString::number(i));
            connect(fontSizeBox, &QComboBox::currentTextChanged, this, &ToolBar::changeFontSize);
            layout1->addWidget(fontSizeBox);

            layout1->addWidget(createButtonWithIcon(":icons/clear.svg", &ToolBar::clearFormatting));

            // Макет с кнопками для выравнивания
            QHBoxLayout *layout2 = new QHBoxLayout();
            layout2->addWidget(createButtonWithIcon(":icons/align_left.svg", &ToolBar::alignLeft));
            layout2->addWidget(createButtonWithIcon(":icons/align_center.svg", &ToolBar::alignCenter));
            layout2->addWidget(createButtonWithIcon(":icons/align_right.svg", &ToolBar::alignRight));
            layout2->addWidget(createButtonWithIcon(":icons/align_justify.svg", &ToolBar::alignJustify));

            // Макет с кнопками для списков
            QHBoxLayout *layout3 = new QHBoxLayout();
            layout3->addWidget(createButtonWithIcon(":icons/bullet_list.svg", &ToolBar::insertBulletList));
            layout3->addWidget(createButtonWithIcon(":icons/numbered_list.svg", &ToolBar::insertNumberedList));

            // Макет для заголовков
            QHBoxLayout *layout4 = new QHBoxLayout();
            QComboBox *headingBox = new QComboBox(this);
            headingBox->addItem("Normal");
            headingBox->addItem("Heading 1");
            headingBox->addItem("Heading 2");
            headingBox->addItem("Heading 3");
            connect(headingBox, &QComboBox::currentTextChanged, this, &ToolBar::changeHeading);
            layout4->addWidget(headingBox);

            // Кнопка вставки таблицы
            layout4->addWidget(createButtonWithIcon(":icons/insert_table.svg", &ToolBar::insertTable));

            // Добавление всех макетов на панель инструментов
            toolBarLayout->addLayout(layout1);
            toolBarLayout->addLayout(layout2);
            toolBarLayout->addLayout(layout3);
            toolBarLayout->addLayout(layout4);

            // Устанавливаем прокручиваемую область с виджетом
            scrollArea->setWidget(toolBarWidget);
            mainLayout->addWidget(scrollArea);
            setLayout(mainLayout);
    }

    QPushButton* createButtonWithIcon(const QString &iconPath, void (ToolBar::*slot)())
    {
        QPushButton *button = new QPushButton();
        QIcon icon(iconPath);  // Загружаем иконку
        button->setIcon(icon);  // Устанавливаем иконку
        button->setIconSize(QSize(32, 32));  // Устанавливаем размер иконки (например, 32x32)
        connect(button, &QPushButton::clicked, this, slot);  // Привязываем слот
        return button;
    }
    void setTextEdit(QTextEdit *newTextEdit)
    {
        textEdit = newTextEdit;
    }

private:
    QPushButton* createButton(const QString& text, void (ToolBar::*slot)()) {
        QPushButton *button = new QPushButton(text, this);
        connect(button, &QPushButton::clicked, this, slot);
        return button;
    }

private slots:
    void changeFont()
    {
        if (!textEdit)
            return;

        bool ok;
        QFont font = QFontDialog::getFont(&ok, textEdit->currentFont(), this);
        if (ok) {
            QTextCursor cursor = textEdit->textCursor();
            QTextCharFormat format;
            format.setFont(font);
            cursor.mergeCharFormat(format);
            textEdit->mergeCurrentCharFormat(format);
        }
    }

    void toggleBold()
    {
        if (!textEdit)
            return;

        QTextCursor cursor = textEdit->textCursor();
        QTextCharFormat format = cursor.charFormat();
        format.setFontWeight(format.fontWeight() == QFont::Bold ? QFont::Normal : QFont::Bold);
        cursor.mergeCharFormat(format);
        textEdit->mergeCurrentCharFormat(format);
    }

    void toggleItalic()
    {
        if (!textEdit)
            return;

        QTextCursor cursor = textEdit->textCursor();
        QTextCharFormat format = cursor.charFormat();
        format.setFontItalic(!format.fontItalic());
        cursor.mergeCharFormat(format);
        textEdit->mergeCurrentCharFormat(format);
    }

    void toggleUnderline()
    {
        if (!textEdit)
            return;

        QTextCursor cursor = textEdit->textCursor();
        QTextCharFormat format = cursor.charFormat();
        format.setFontUnderline(!format.fontUnderline());
        cursor.mergeCharFormat(format);
        textEdit->mergeCurrentCharFormat(format);
    }

    void changeColor()
    {
        if (!textEdit)
            return;

        QColor color = QColorDialog::getColor(Qt::black, this);
        if (color.isValid()) {
            QTextCursor cursor = textEdit->textCursor();
            QTextCharFormat format;
            format.setForeground(color);
            cursor.mergeCharFormat(format);
            textEdit->mergeCurrentCharFormat(format);
        }
    }

    void changeBgColor()
    {
        if (!textEdit)
            return;

        QColor color = QColorDialog::getColor(Qt::white, this);
        if (color.isValid()) {
            QTextCursor cursor = textEdit->textCursor();
            QTextCharFormat format;
            format.setBackground(color);
            cursor.mergeCharFormat(format);
            textEdit->mergeCurrentCharFormat(format);
        }
    }

    void changeFontSize(const QString &size)
    {
        if (!textEdit)
            return;

        bool ok;
        int fontSize = size.toInt(&ok);
        if (ok) {
            QTextCursor cursor = textEdit->textCursor();
            QTextCharFormat format;
            format.setFontPointSize(fontSize);
            cursor.mergeCharFormat(format);
            textEdit->mergeCurrentCharFormat(format);
        }
    }

    void alignLeft()
    {
        if (textEdit)
            textEdit->setAlignment(Qt::AlignLeft);
    }

    void alignCenter()
    {
        if (textEdit)
            textEdit->setAlignment(Qt::AlignCenter);
    }

    void alignRight()
    {
        if (textEdit)
            textEdit->setAlignment(Qt::AlignRight);
    }

    void alignJustify()
    {
        if (textEdit)
            textEdit->setAlignment(Qt::AlignJustify);
    }

    void clearFormatting()
    {
        if (!textEdit)
            return;

        QTextCursor cursor = textEdit->textCursor();
        QTextCharFormat format;
        cursor.setCharFormat(format);
        textEdit->mergeCurrentCharFormat(format);
    }

    void insertBulletList()
    {
        if (!textEdit)
            return;

        QTextCursor cursor = textEdit->textCursor();
        QTextListFormat listFormat;
        listFormat.setStyle(QTextListFormat::ListDisc);
        cursor.createList(listFormat);
    }

    void insertNumberedList()
    {
        if (!textEdit)
            return;

        QTextCursor cursor = textEdit->textCursor();
        QTextListFormat listFormat;
        listFormat.setStyle(QTextListFormat::ListDecimal);
        cursor.createList(listFormat);
    }

    void changeHeading(const QString &heading)
    {
        if (!textEdit)
            return;

        QTextCursor cursor = textEdit->textCursor();
        QTextBlockFormat blockFormat = cursor.blockFormat();

        if (heading == "Heading 1")
            blockFormat.setHeadingLevel(1);
        else if (heading == "Heading 2")
            blockFormat.setHeadingLevel(2);
        else if (heading == "Heading 3")
            blockFormat.setHeadingLevel(3);
        else
            blockFormat.setHeadingLevel(0);

        cursor.setBlockFormat(blockFormat);
    }

    void insertTable()
    {
        if (!textEdit)
            return;

        bool ok;
        int rows = QInputDialog::getInt(this, "Insert Table", "Rows:", 2, 1, 100, 1, &ok);
        if (!ok) return;

        int columns = QInputDialog::getInt(this, "Insert Table", "Columns:", 2, 1, 100, 1, &ok);
        if (!ok) return;

        QTextCursor cursor = textEdit->textCursor();
        QTextTableFormat tableFormat;
        tableFormat.setBorder(1);
        tableFormat.setCellSpacing(12);
        tableFormat.setCellPadding(12);
        cursor.insertTable(rows, columns, tableFormat);
    }

private:
    QTextEdit *textEdit;
};

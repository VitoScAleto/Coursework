FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    qtbase5-dev \
    qt5-qmake \
    libqt5printsupport5 \
    libqt5core5a \
    libqt5gui5 \
    libqt5widgets5 \
    && apt-get clean
# Копируем содержимое папки QtRelease в контейнер
COPY QtRelease /QtRelease

# Устанавливаем рабочую директорию
WORKDIR /QtRelease

# Указываем команду для выполнения
ENTRYPOINT ["./Course_work"] 
# TreeModel
Иерархическая модель Qt в паре с делегатом

Загрузить XML файл в объект QDomDocument с помощью метода QDomDocument::setContent().
Найти элемент в XML документе, у которого нужно изменить текст между тегами. Это можно сделать с помощью метода QDomDocument::elementsByTagName().
Изменить текст между тегами элемента с помощью метода QDomNode::toElement().setText().
Сохранить измененный XML документ в файл с помощью метода QDomDocument::save().
Ниже приведен пример кода на C++, который демонстрирует, как изменить текст между тегами с помощью класса QDomDocument:

cpp
Copy code
#include <QtXml>

int main()
{
    // Загрузить XML файл в объект QDomDocument
    QDomDocument doc;
    QFile file("input.xml");
    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file))
        return 1;

    // Найти элемент в XML документе, у которого нужно изменить текст между тегами
    QDomNodeList nodes = doc.elementsByTagName("title");
    if (nodes.size() > 0)
    {
        // Изменить текст между тегами элемента
        nodes.at(0).toElement().setText("New Title");
    }

    // Сохранить измененный XML документ в файл
    QFile outFile("output.xml");
    if (!outFile.open(QIODevice::WriteOnly) || !doc.save(&outFile))
        return 1;

    return 0;
}
В этом примере мы ищем первый элемент с тегом "title" и изменяем его текст на "New Title". Затем мы сохраняем измененный XML документ в файл "output.xml".

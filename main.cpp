#include <iostream>
#include "model.h"
int main() {
    Model model;
    // инициализация модели
    model.positions = {0.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f};
    model.normals = {0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};
    model.uvs = {0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f};
    model.indices = {0, 1, 2};
    model.textureName = "texture.png";

    // записываем модель в файл
    model.writeToFile("model.bin");

    // читаем модель из файла
    Model loadedModel;
    loadedModel.readFromFile("model.bin");

    // выводим информацию о модели
    cout << "Loaded model: " << endl;
    cout << "Vertex count: " << loadedModel.positions.size() / 3 << endl;
    cout << "Texture name: " << loadedModel.textureName << endl;

    return 0;
}
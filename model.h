//
// Created by valie on 10.03.2023.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Model {
public:
    vector<float> positions; // позиции вертексов
    vector<float> normals; // нормали вертексов
    vector<float> uvs; // UV-координаты вертексов
    vector<int> indices; // индексы вертексов
    string textureName; // название текстуры

    void writeToFile(const char *filename) {
        ofstream file(filename, ios::binary);
        if (file.is_open()) {
            int vertexCount = positions.size() / 3;
            file.write((char *) &vertexCount, sizeof(int));
            file.write((char *) positions.data(), sizeof(float) * positions.size());
            file.write((char *) normals.data(), sizeof(float) * normals.size());
            file.write((char *) uvs.data(), sizeof(float) * uvs.size());
            int indexCount = indices.size();
            file.write((char *) &indexCount, sizeof(int));
            file.write((char *) indices.data(), sizeof(int) * indices.size());
            int textureNameLength = textureName.size() + 1;
            file.write((char *) &textureNameLength, sizeof(int));
            file.write(textureName.c_str(), textureNameLength);
            file.close();
        } else {
            cout << "Error: cannot open file " << filename << " for writing." << endl;
        }
    }

    void readFromFile(const char *filename) {
        ifstream file(filename, ios::binary);
        if (file.is_open()) {
            int vertexCount;
            file.read((char *) &vertexCount, sizeof(int));
            positions.resize(vertexCount * 3);
            file.read((char *) positions.data(), sizeof(float) * positions.size());
            normals.resize(vertexCount * 3);
            file.read((char *) normals.data(), sizeof(float) * normals.size());
            uvs.resize(vertexCount * 2);
            file.read((char *) uvs.data(), sizeof(float) * uvs.size());
            int indexCount;
            file.read((char *) &indexCount, sizeof(int));
            indices.resize(indexCount);
            file.read((char *) indices.data(), sizeof(int) * indices.size());
            int textureNameLength;
            file.read((char *) &textureNameLength, sizeof(int));
            char *texture = new char[textureNameLength];
            file.read(texture, textureNameLength);
            textureName = texture;
            delete[] texture;
            file.close();
        } else {
            cout << "Error: cannot open file " << filename << " for reading." << endl;
        }
    }
};


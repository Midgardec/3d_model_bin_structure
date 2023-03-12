#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

// Класс Model определяет модель 3D объекта, хранящую информацию о вершинах, индексах, нормалях, UV-координатах и текстуре.
// Имеет методы для записи и чтения модели из файла в двоичном формате.


class Model {
public:
    std::vector<float> positions;   // позиции вертексов
    std::vector<float> normals;     // нормали вертексов
    std::vector<float> uvs;         // UV-координаты вертексов
    std::vector<int> indices;       // индексы вертексов
    std::string textureName;        // название текстуры


    // Записывает модель в двоичный файл с заданным именем файла
    void writeToFile(const std::string& filename) {
        try {
            std::ofstream file(filename, std::ios::binary);
            if (!file) {
                throw std::runtime_error("Error: cannot open file for writing.");
            }


            // Проверяем размеры массивов данных
            if (positions.size() % 3 != 0 || normals.size() % 3 != 0 || uvs.size() % 2 != 0) {
                throw std::runtime_error("Error: invalid array size for vertex data.");
            }

            // Проверяем совместимость индексов
            for (int index : indices) {
                if (index < 0 || index >= positions.size() / 3) {
                    throw std::runtime_error("Error: invalid vertex index in index buffer.");
                }
            }


            int vertexCount = static_cast<int>(positions.size() / 3);                // вычисление количества вершин модели

            file.write(reinterpret_cast<char*>(&vertexCount), sizeof(int));    // запись количества вершин в файл
            file.write(reinterpret_cast<char*>(positions.data()), sizeof(float) * positions.size());    // запись позиций вершин в файл
            file.write(reinterpret_cast<char*>(normals.data()), sizeof(float) * normals.size());        // запись нормалей вершин в файл

            file.write(reinterpret_cast<char*>(uvs.data()), sizeof(float) * uvs.size());                // запись UV-координат вершин в файл

            int indexCount = static_cast<int>(indices.size());                      // вычисление количества индексов модели
            file.write(reinterpret_cast<char*>(&indexCount), sizeof(int));    // запись количества индексов в файл
            file.write(reinterpret_cast<char*>(indices.data()), sizeof(int) * indices.size());          // запись индексов вершин в файл

            int textureNameLength = static_cast<int>(textureName.size() + 1);       // вычисление длины названия текстуры
            file.write(reinterpret_cast<char*>(&textureNameLength), sizeof(int));                       // запись длины названия текстуры в файл
            file.write(textureName.c_str(), textureNameLength);                // запись названия текстуры в файл

            file.close();                                                          // закрытие потока
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }


    // Читает модель из двоичного файла с заданным именем файла
    void readFromFile(const std::string& filename) {
        try {
            std::ifstream file(filename, std::ios::binary);
            if (!file) {
                throw std::runtime_error("Error: cannot open file for reading.");
            }

            int vertexCount;
            file.read(reinterpret_cast<char*>(&vertexCount), sizeof(vertexCount));
            if (file.gcount() != sizeof(vertexCount)) {
                throw std::runtime_error("Error: failed to read vertex count from file.");
            }

            positions.resize(vertexCount * 3);
            file.read(reinterpret_cast<char*>(positions.data()), sizeof(float) * positions.size());
            if (file.gcount() != sizeof(float) * positions.size()) {
                throw std::runtime_error("Error: failed to read vertex positions from file.");
            }

            normals.resize(vertexCount * 3);
            file.read(reinterpret_cast<char*>(normals.data()), sizeof(float) * normals.size());
            if (file.gcount() != sizeof(float) * normals.size()) {
                throw std::runtime_error("Error: failed to read vertex normals from file.");
            }

            uvs.resize(vertexCount * 2);
            file.read(reinterpret_cast<char*>(uvs.data()), sizeof(float) * uvs.size());
            if (file.gcount() != sizeof(float) * uvs.size()) {
                throw std::runtime_error("Error: failed to read vertex UVs from file.");
            }

            int indexCount;
            file.read(reinterpret_cast<char*>(&indexCount), sizeof(indexCount));
            if (file.gcount() != sizeof(indexCount)) {
                throw std::runtime_error("Error: failed to read index count from file.");
            }

            indices.resize(indexCount);
            file.read(reinterpret_cast<char*>(indices.data()), sizeof(int) * indices.size());
            if (file.gcount() != sizeof(int) * indices.size()) {
                throw std::runtime_error("Error: failed to read indices from file.");
            }

            int textureNameLength;
            file.read(reinterpret_cast<char*>(&textureNameLength), sizeof(textureNameLength));
            if (file.gcount() != sizeof(textureNameLength)) {
                throw std::runtime_error("Error: failed to read texture name length from file.");
            }

            char* textureNameBuffer = new char[textureNameLength];
            file.read(textureNameBuffer, textureNameLength);
            if (file.gcount() != textureNameLength) {
                delete[] textureNameBuffer;
                throw std::runtime_error("Error: failed to read texture name from file.");
            }

            textureName = std::string(textureNameBuffer);
            delete[] textureNameBuffer;

            file.close();
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
};
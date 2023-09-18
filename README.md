# Лабораторная работа № 1. Основной математический аппарат
## 1. Бинарное представление данных.

void printFile(const std::string& format, const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);

    if (!file) {
        std::cerr << "Cann't open file: " << filePath << std::endl;
        return;
    }

    unsigned char byte;
    while (file.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
        if (format == "hex8") {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
        }
        else if (format == "dec8") {
            std::cout << std::dec << std::setw(3) << std::setfill('0') << static_cast<int>(byte) << " ";
        }
        else if (format == "hex16") {
            std::cout << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(byte) << " ";
        }
        else if (format == "dec16") {
            std::cout << std::dec << std::setw(5) << std::setfill('0') << static_cast<int>(byte) << " ";
        }
        else if (format == "hex32") {
            std::cout << std::hex << std::setw(8) << std::setfill('0') << static_cast<int>(byte) << " ";
        }
        else {
            std::cerr << "Unknown format: " << format << std::endl;
            return;
        }
    }

    file.close();
}

#include <iostream>
#include "libusb.h"

/**
 Product ID:    0x1a64
 Vendor ID:    0x0b05  (ASUSTek Computer Inc.)
 Manufacturer:    ASUSTeK
 */
#define ASUS_VENDOR_ID 0x0b05
#define ASUS_PRODUCT_ID 0x1a64

int main() {
    libusb_context* context = nullptr;
    libusb_device** device_list = nullptr;
    libusb_device* device = nullptr;
    libusb_device_descriptor desc;

    // Инициализация libusb
    if (libusb_init(&context) != 0) {
        std::cerr << "Ошибка инициализации libusb" << std::endl;
        return 1;
    }

    // Получение списка устройств
    ssize_t count = libusb_get_device_list(context, &device_list);
    if (count < 0) {
        std::cerr << "Ошибка получения списка устройств" << std::endl;
        libusb_exit(context);
        return 1;
    }

    // Поиск ASUS ROG клавиатуры
    for (ssize_t i = 0; i < count; ++i) {
        device = device_list[i];
        if (libusb_get_device_descriptor(device, &desc) == 0) {
            if (desc.idVendor == ASUS_VENDOR_ID && desc.idProduct == ASUS_PRODUCT_ID) {
                std::cout << "ASUS ROG клавиатура обнаружена!" << std::endl;
                
                
                // Ваш код для управления цветом клавиатуры
                break;
            }
        }
    }

    // Освобождение ресурсов
    libusb_free_device_list(device_list, 1);
    libusb_exit(context);

    return 0;
}

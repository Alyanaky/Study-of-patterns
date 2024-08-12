#include <iostream>
#include <vector>
#include <string>
#include <map> // Подключите заголовочный файл для map

// Интерфейс для стратегии доставки
class ShippingStrategy {
public:
    virtual void shipOrder(const std::string& address) = 0;
};

// Конкретная реализация стандартной доставки
class StandardShipping : public ShippingStrategy {
public:
    void shipOrder(const std::string& address) override {
        std::cout << "Доставка стандартной почтой по адресу: " << address << std::endl;
    }
};

// Конкретная реализация экспресс-доставки
class ExpressShipping : public ShippingStrategy {
public:
    void shipOrder(const std::string& address) override {
        std::cout << "Доставка экспресс-почтой по адресу: " << address << std::endl;
    }
};

// Класс для хранения запасов
class Stock {
public:
    void addClothes(const std::string& name, int quantity) {
        clothes[name] += quantity;
    }

    int getQuantity(const std::string& name) const {
        return clothes.at(name);
    }

private:
    std::map<std::string, int> clothes; // clothes в private
};

// Класс для обработки платежей
class Checkout {
public:
    void processPayment(double amount) {
        std::cout << "Оплата " << amount << " успешно обработана" << std::endl;
    }
};

// Класс для доставки заказов
class Delivery {
public:
    void deliverOrder(const std::string& address) {
        std::cout << "Заказ доставлен по адресу: " << address << std::endl;
    }
};

// Фасад для магазина одежды
class ClothingStore {
public:
    ClothingStore() : stock(), checkout(), delivery() {}

    // Добавление товара в запасы
    void addClothes(const std::string& name, int quantity) {
        stock.addClothes(name, quantity);
    }

    // Заказ товара
    void orderClothes(const std::string& name, int quantity, const std::string& address,
        ShippingStrategy* strategy) {
        if (stock.getQuantity(name) >= quantity) {
            stock.addClothes(name, -quantity);
            checkout.processPayment(calculatePrice(name, quantity));
            strategy->shipOrder(address);
        }
        else {
            std::cout << "Недостаточно товара на складе." << std::endl;
        }
    }

private:
    double calculatePrice(const std::string& name, int quantity) {
        // Упрощенная логика расчета цены
        return quantity * 10.0;
    }

    Stock stock;
    Checkout checkout;
    Delivery delivery;
};

int main() {
    setlocale(LC_ALL, "Russian");
    // Создание магазина
    ClothingStore store;

    // Добавление товаров на склад
    store.addClothes("Футболка", 10);
    store.addClothes("Штаны", 5);

    // Заказ товара со стандартной доставкой
    std::cout << "Заказ футболки со стандартной доставкой:" << std::endl;
    store.orderClothes("Футболка", 2, "ул. Ленина, 1", new StandardShipping());

    // Заказ товара с экспресс-доставкой
    std::cout << "Заказ штанов с экспресс-доставкой:" << std::endl;
    store.orderClothes("Штаны", 1, "пр. Мира, 15", new ExpressShipping());

    return 0;
}

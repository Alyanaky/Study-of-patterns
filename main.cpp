#include <iostream>
#include <vector>
#include <string>
#include <map> // ���������� ������������ ���� ��� map

// ��������� ��� ��������� ��������
class ShippingStrategy {
public:
    virtual void shipOrder(const std::string& address) = 0;
};

// ���������� ���������� ����������� ��������
class StandardShipping : public ShippingStrategy {
public:
    void shipOrder(const std::string& address) override {
        std::cout << "�������� ����������� ������ �� ������: " << address << std::endl;
    }
};

// ���������� ���������� ��������-��������
class ExpressShipping : public ShippingStrategy {
public:
    void shipOrder(const std::string& address) override {
        std::cout << "�������� ��������-������ �� ������: " << address << std::endl;
    }
};

// ����� ��� �������� �������
class Stock {
public:
    void addClothes(const std::string& name, int quantity) {
        clothes[name] += quantity;
    }

    int getQuantity(const std::string& name) const {
        return clothes.at(name);
    }

private:
    std::map<std::string, int> clothes; // clothes � private
};

// ����� ��� ��������� ��������
class Checkout {
public:
    void processPayment(double amount) {
        std::cout << "������ " << amount << " ������� ����������" << std::endl;
    }
};

// ����� ��� �������� �������
class Delivery {
public:
    void deliverOrder(const std::string& address) {
        std::cout << "����� ��������� �� ������: " << address << std::endl;
    }
};

// ����� ��� �������� ������
class ClothingStore {
public:
    ClothingStore() : stock(), checkout(), delivery() {}

    // ���������� ������ � ������
    void addClothes(const std::string& name, int quantity) {
        stock.addClothes(name, quantity);
    }

    // ����� ������
    void orderClothes(const std::string& name, int quantity, const std::string& address,
        ShippingStrategy* strategy) {
        if (stock.getQuantity(name) >= quantity) {
            stock.addClothes(name, -quantity);
            checkout.processPayment(calculatePrice(name, quantity));
            strategy->shipOrder(address);
        }
        else {
            std::cout << "������������ ������ �� ������." << std::endl;
        }
    }

private:
    double calculatePrice(const std::string& name, int quantity) {
        // ���������� ������ ������� ����
        return quantity * 10.0;
    }

    Stock stock;
    Checkout checkout;
    Delivery delivery;
};

int main() {
    setlocale(LC_ALL, "Russian");
    // �������� ��������
    ClothingStore store;

    // ���������� ������� �� �����
    store.addClothes("��������", 10);
    store.addClothes("�����", 5);

    // ����� ������ �� ����������� ���������
    std::cout << "����� �������� �� ����������� ���������:" << std::endl;
    store.orderClothes("��������", 2, "��. ������, 1", new StandardShipping());

    // ����� ������ � ��������-���������
    std::cout << "����� ������ � ��������-���������:" << std::endl;
    store.orderClothes("�����", 1, "��. ����, 15", new ExpressShipping());

    return 0;
}

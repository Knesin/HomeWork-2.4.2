#include <iostream>
#include <fstream>
#include <string>


class Address {
public:
    void set_city(const std::string &str) { city_ = str; }
    void set_street(const std::string &str) { street_ = str; }
    void set_home(const int &number) { home_ = number; }
    void set_apartment(const int &number) { apartment_ = number; }
    std::string get_city() { return city_; }
    std::string get_street() { return street_; }
    int get_home() { return home_; }
    int get_apartment() { return apartment_; }

    std::string get_output_address();
    Address(const std::string &c, const std::string &s, const int &h, const int &a);
private:
    std::string city_;
    std::string street_;
    int home_;
    int apartment_;
};

std::string Address::get_output_address() {
    std::string tmp_str;
    tmp_str =  city_ + ", " +
               street_ + ", " +
               std::to_string(home_) + ", "+
               std::to_string(apartment_);
    return tmp_str;
}

Address::Address(const std::string& c, const std::string& s, const int& h, const int& a) {
    city_ = c;
    street_ = s;
    home_ = h;
    apartment_ = a;
}

void delete_class(Address** arr, const int& r)
{
    for (int i = 0; i < r; ++i) {
        delete arr[i];
        arr[i] = nullptr;
    }
    delete[] arr;
    arr = nullptr;
}

void sort_city(Address** adr, const int& c) {
    Address* tmp;
    bool change = false;
    do{
        change = false;
        for (int i = 0; i < c-1; ++i) {
            if (adr[i]->get_city() > adr[i + 1]->get_city()) {
                tmp = adr[i];
                adr[i] = adr[i + 1];
                adr[i + 1] = tmp;
                change = true;
            }
        }
    } while (change);
}

int main()
{
    std::ifstream in_f("in.txt");
    std::ofstream out_f("out.txt");
    int count = 0;
    Address** adres;

    setlocale(LC_ALL, "Russian");
    if (!in_f.is_open()) {
        std::cout << "Не удолось открыть файл" << std::endl;
        return 1;
    }
    in_f >> count;
    adres = new Address* [count];

    for (int i = 0; i < count; ++i) {
        std::string str_c;
        std::string str_s;
        int int_h;
        int int_a;
        in_f >> str_c;       
        in_f >> str_s;      
        in_f >> int_h;       
        in_f >> int_a;

        adres[i] = new Address(str_c, str_s, int_h, int_a);
    }

    sort_city(adres, count);

    out_f << count << std::endl;
    for (int i = 0; i < count; ++i) {
        out_f << adres[i]->get_output_address();
        if (i < count-1 )
            out_f << std::endl;
    }

    delete_class(adres, count);
    in_f.close();
    out_f.close();
}
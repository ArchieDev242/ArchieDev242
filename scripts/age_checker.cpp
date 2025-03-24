#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

int main()
{
    int year = 2006, month = 9, day = 18;  // date of birth

    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    int current_year = now -> tm_year + 1900;
    int current_month = now -> tm_mon + 1;
    int current_day = now -> tm_mday;

    int age = current_year - year;

    if(current_month < month || (current_month == month && current_day < day))
    {
        age--;
    }

    // working with README file
    std::string readme_path = "README.md";

    // changing years info
    std::ifstream in_file(readme_path);
    std::string content((std::istreambuf_iterator<char>(in_file)), std::istreambuf_iterator<char>());
    in_file.close();

    std::string old_age_str = "***" + std::to_string(age - 1) + " y.o.***";
    std::string new_age_str = "***" + std::to_string(age) + " y.o.***";
    size_t pos = content.find(old_age_str);

    if(pos != std::string::npos) 
    {
        content.replace(pos, old_age_str.length(), new_age_str);
    }

    std::ofstream out_file(readme_path);
    out_file << content;
    out_file.close();

    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

int main()
{
    int year = 2006, month = 9, day = 18;  // date of birth (test)

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

    if(!in_file.is_open())
    {
        std::cerr << "Cannot open the file: " << readme_path << std::endl;
        return 1;
    }

    std::string content((std::istreambuf_iterator<char>(in_file)), std::istreambuf_iterator<char>());
    in_file.close();
    
    // find suffix
    const std::string suffix = " y.o.***";
    size_t end_pos = content.find(suffix);

    if(end_pos == std::string::npos)
    {
        std::cerr << "Marker not found in README\n" << std::endl;
        return 1;
    }

    // find prefix
    size_t start_pos = content.rfind("***", end_pos);

    if(start_pos == std::string::npos)
    {
        std::cerr << "Opening marker not found in README\n" << std::endl;
        return 1;
    }

    start_pos += 3;
    std::string current_age_str = content.substr(start_pos, end_pos - start_pos);
    std::string new_age_str = std::to_string(age);

    if(current_age_str == new_age_str)
    {
        std::cout << "Age already up to date: " << age << std::endl;
        return 0;
    }

    content.replace(start_pos, end_pos - start_pos, new_age_str); // replace an old age in the content
    std::ofstream out_file(readme_path);
    out_file << content;
    out_file.close();

    std::cout << "Age updated to: " << age << std::endl;
    return 0;
}

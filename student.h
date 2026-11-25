#pragma once
#include <string>
#include <iostream>

// 2. 클래스1.h: 지난 실습에서 사용한 클래스에 다음을 변경 



namespace ywchoi2649052
{
    class student 
    {
    protected:
        std::string name{};
        int id{};
        int score{};
        char grade{};	
        
        void testId(){
            if (id < 1000000 || id > 9999999)
            {
                std::cout << "Invalid ID\n";
                std::exit(1);
            }    
        }

        void testScore(){
            if (score < 0 || score > 100)
            {
                std::cout << "Invalid score\n";
                std::exit(1);
            }    
        }

        void calGrade()
        {
            if (score >= 90) grade = 'A';
            else if (score >= 80) grade = 'B';
            else if (score >= 70) grade = 'C';
            else if (score >= 60) grade = 'D';
            else grade = 'F';
        }

    public:

        student(const std::string& n = "no name yet", int d = 1234567, int s = 0) 
        : name{n}, id{d}, score{s}{
            testId(); testScore(); calGrade();
        }

        // -input: 매개변수를 std::istream&로, 기본값은 std::cin으로
        //student s; s.input();
        void input(std::istream& is = std::cin)
        { //std::cin --> is
            std::cout << "Enter name: "; 
            std::getline(is >> std::ws, name);
            std::cout << "Enter id: ";   
            is >> id; testId();
            std::cout << "Enter score: ";
            is >> score; testScore();
            calGrade();
        }

        // -입력연산자>>: input함수를 이용
        friend std::istream& operator>>(std::istream& is, student& s)
        {
            s.input(is);
            return is;
        }

        void setName(const std::string& n){name = n;}
        void setId(int d){id = d; testId();}
        void setScore(int s){score = s; testScore();}
        void setGrade(char g){grade = g;}

        // -print: 매개변수를 std::ostream&로, 기본값은 std::cout으로, 공백채움문자설정과 출력폭설정으로 변경하기

        void print(std::ostream& os = std::cout) const 
        {
            os << name << "(" << id << "): ";
            os.width(3); os.fill('0'); 
            os << score << "(" << grade << ")\n";
        }

        // -출력연산자<<: print함수를 이용
        friend std::ostream& operator<<(std::ostream& os, const student& s) 
        {
            s.print(os);
            return os;
        }

        const std::string& getName() const {return name;}
        int getId() const {return id;}
        int getScore() const {return score;}
        char getGrade() const{return grade;}
        student& operator++(){++score; calGrade(); return *this;}
        student operator++(int)
        { 
            student temp{*this};
            ++(*this);
            return temp; 
        }
        student& operator+=(int s)
        {
            score += s; 
            if(score > 100) score = 100;
            calGrade();
            return *this;
        }

        friend bool operator==(const student& s1, const student& s2) { return s1.id == s2.id;}
        friend int operator+(const student& s1, const student& s2) { return s1.score + s2.score;}

    };

}
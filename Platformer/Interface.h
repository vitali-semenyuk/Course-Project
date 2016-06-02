#pragma once

#include "Global.h"

class Label {
protected:
    double x, y;
    sf::Text labelText;
    std::wstring text;

public:
    virtual void create(std::wstring text, sf::Font &font, double x = 0, double y = 0);
    sf::Text displayText();
    sf::FloatRect getBounds();
    void setPosition(int x, int y);
};

class Button : public Label {
protected:
    double width, height;
    sf::RectangleShape box;

public:
    void create(std::wstring text, sf::Font &font, double x = 0, double y = 0, double width = 150, double height = 30);
    sf::RectangleShape displayButton();
    bool select(sf::Vector2i mouse);
};

class Input : public Button {
protected:
    bool focus;
public:
    void create(sf::Font &font, std::wstring _text = L"", double _x = 0, double _y = 0, double _width = 150, double _height = 30);
    void reText(wchar_t _tmp);

    // �������� ������ Input
    bool select();

    // ��������� ������ Input
    bool select(sf::Vector2i _mouse);

    //��� ����, ��� �� ������� ����� � ���� Ipnut ���������� ���������  readText() ������� ���������� string
    std::wstring readText();
    sf::FloatRect getBounds();
    void setPosition(int x, int y);
};
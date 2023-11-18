//1.5
#include<iostream>
#include<vector>
using namespace std;

class RGB
{
public:
    int R, G, B;
    RGB(int _R = 0, int _G = 0, int _B = 0)
    {
        if (_R < 0) { _R = 0; }
        if (_R > 255) { _R = 255; }
        R = _R;
        if (_G < 0) { _G = 0; }
        if (_G > 255) { _G = 255; }
        G = _G;
        if (_B < 0) { _B = 0; }
        if (_B > 255) { _B = 255; }
        B = _B;
    }
};

class figure
{
public:
    figure(vector<float> _sides = {}, RGB _color = RGB())
    {
        sides = _sides;
        color = _color;
        if (!possible()) { sides = {}; }
    }
    bool possible()
    {
        size_t n = sides.size();
        bool possible = n > 2;
        for (size_t i = 0; i < n && possible; i++)
        {
            float sum = 0;
            for (size_t j = 0; j < n; j++) { sum += sides[j] * (j != i); }
            if (sum < sides[i]) { possible = false; }
        }
        return possible;
    }
    void print()
    {
        size_t n = sides.size();
        for (size_t i = 0; i < n; i++) { cout << sides[i] << '\t'; }
        cout << endl << 'R' << color.R << 'G' << color.G << 'B' << color.B << endl << endl;
    }
    vector<float> get_sides()
    {
        return sides;
    }
private:
    vector<float> sides;
    RGB color;
};

figure randomTriangle()
{
    figure tmp_figure;
    RGB tmp_color(rand() % 255, rand() % 255, rand() % 255);
    for (; !tmp_figure.possible();)
    {
        vector<float> tmp_sides(3);
        for (size_t i = 0; i < 3; i++) { tmp_sides[i] = float(rand() % 10 + (rand() % 10) / 10.0); }
        tmp_figure = figure(tmp_sides, tmp_color);
    }
    return tmp_figure;
}

int task1()
{
    unsigned int seed = -0;
    if (!seed) { seed = time(0); }
    cout << "seed: " << seed << endl << endl;
    srand(seed);

    for (int i = 0; i < 10; i++)
    {
        figure tmp = randomTriangle();
        tmp.print();
    }
    return 0;
}
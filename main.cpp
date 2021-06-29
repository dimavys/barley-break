
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

// this is for github
#include <SFML/Graphics.hpp>
#define n 4
#define size n*n
#define window_size 1000
#define square 240
#include "ResourcePath.hpp"
const int cof = 2;
class Game : public sf::Drawable, public sf::Transformable
{

public:
    int elements[size];
    int empty_index;
    bool solved;
    sf::Font font;
    Game();
    void Init();
    bool Check();
    void Move(char command);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

Game::Game()
{
    font.loadFromFile(resourcePath() + "Maxellight.ttf");
    Init();
}

void Game::Init()
{
    
    for (int i = 0; i < size - 1; i++)
    {
    elements[i] = i + 1; // writing numbers in array
    }
    empty_index = size - 1;
    elements[empty_index] = 0;   // last number is zero
    solved = true; // fixing that it is solved
}

bool Game::Check()
{
    for ( int i = 0; i <size; i++)
    {
        if (elements[i] > 0 && elements[i] != i + 1)
        {
            return false;
        }
    }
    return true;
}

void Game::Move(char command)
{
    // initalizing empty position
    int col = empty_index % n;
    int row = empty_index / n;

   //searching neighbour position due to command
    int move_index = -1;
    if ((command == 'l') && (col < (n - 1)))
    {
        move_index = empty_index + 1;
    }
    if ((command == 'r') && (col > 0))
    {
        move_index = empty_index - 1;
    }
    if ((command == 'u') && (row < (n - 1)))
    {
        move_index = empty_index + n;
    }
    if ((command == 'd') && (row > 0))
    {
        move_index = empty_index - n;
    }

    // swapping
    if ((empty_index >= 0) && (move_index >= 0))
    {
        int temp = elements[empty_index];
        elements[empty_index] = elements[move_index];
        elements[move_index] = temp;
        empty_index = move_index;
    }
    solved = Check();
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    sf::Color color = sf::Color(200, 100, 200);
    sf::Color color_golf = sf::Color(204, 214, 19); // setting gold color
    sf::RectangleShape shape(sf::Vector2f(window_size, window_size)); // creating a field
    shape.setOutlineThickness(3.f);
    shape.setOutlineColor(color_golf);
    shape.setFillColor(color_golf);
    target.draw(shape, states);
    
    shape.setSize(sf::Vector2f(square - 2, square - 2));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(color_golf);
    shape.setFillColor(sf::Color::Black);

  
    sf::Text text_pl("", font, 52 * cof);

    for ( int i = 0; i < size; i++)
    {
        shape.setOutlineColor(color_golf);
        text_pl.setFillColor(color_golf);
        text_pl.setString(std::to_string(elements[i]));
        if (solved)
                {
                    target.clear();
                    sf::Text labelMenu("Menu", font, 20 * cof);
                    labelMenu.setFillColor(color_golf);
                    labelMenu.setPosition(250.f *cof - 50, 170 * cof);
                    target.draw(labelMenu, states);
                    
                    sf::Text descMenu("Start new game - 1 | Exit - Esc ", font, 20 * cof);
                    descMenu.setFillColor(color_golf);
                    descMenu.setPosition(250.f, 200.f * cof);
                    target.draw(descMenu, states);
                    shape.setOutlineColor(color_golf);
                    shape.setFillColor(color_golf);
                    text_pl.setFillColor(color_golf);
                    
                }
        if (elements[i] > 0)
        {
            sf::Vector2f position(i % n * square + 10.f * cof, i / n * square + 10.f * cof);
            shape.setPosition(position);
            text_pl.setPosition(position.x + 35.f * cof + (elements[i] < 10 ? 15.f : 0.f), position.y + 25.f * cof);
            target.draw(shape, states);
            target.draw(text_pl, states);
        }
    }
}



int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(500 * cof, 550 * cof), "Made by Vysotskyy");
    window.setFramerateLimit(60);
    sf::Font font;
    if(!font.loadFromFile(resourcePath() + "Maxellight.ttf")){ // connecting a font
        return 0;
    }
    Game game; // creating a game
    game.setPosition(0,100);
    sf::Event event;
    int move_times = 0;    //counter for mixing it up
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                
                if(!game.solved){ //you can't press one of those keys if the game wasn't started
                    
                    if (event.key.code == sf::Keyboard::Left)
                    {
                        game.Move('l');
                    }
                    if (event.key.code == sf::Keyboard::Right)
                    {
                        game.Move('r');
                    }
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        game.Move('u');
                    }
                    if (event.key.code == sf::Keyboard::Down)
                    {
                        game.Move('d');
                    }
                }
                // starting game
                if (event.key.code == sf::Keyboard::Num1)
                {
                    game.Init();
                    move_times = 100; // 100 times of swapping
                }
            }
            
        }
            char ar[4] = {'l','r','u','d'}; // array of commands
            if (move_times-- > 0)
            {
                (game.Move(ar[rand()%4])); //getting rand of commands
            }
            window.clear();
            window.draw(game);
            window.display();
    }
        return 0;
    }



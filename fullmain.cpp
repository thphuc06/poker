#include "fullDeclare.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/**
 * Main function implements the game's UI and game loop
 * Features:
 * - Start menu with multiple game modes
 * - Player registration system
 * - Interactive card game
 * - Statistics tracking
 */

enum game_state {
    start,
    sign,
    mode1,
    mode2,
    mode3,
    mode4
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 1000), "GamePoker");
    window.setFramerateLimit(60);

    sf::Color customColor(184, 134, 11); //gold color
    sf::Color dark_blue(0, 70, 140); //blue font

    sf::Font font;
    if (!font.loadFromFile("C:/HCMUS/arial.ttf"))
    {
        return -1;
    }

    sf::Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(200.f, 200.f);

    sf::Text promptText;
    promptText.setFont(font);
    promptText.setCharacterSize(24);
    promptText.setFillColor(sf::Color::Yellow);
    promptText.setPosition(200.f, 100.f);
    promptText.setString("Enter the number of players:");

    sf::RectangleShape playButton(sf::Vector2f(150.f, 50.f));
    playButton.setFillColor(sf::Color::Green);
    playButton.setPosition(325.f, 400.f);

    sf::Text playButtonText;
    playButtonText.setFont(font);
    playButtonText.setCharacterSize(20);
    playButtonText.setFillColor(sf::Color::White);
    playButtonText.setString("Play");
    playButtonText.setPosition(365.f, 410.f);

    sf::RectangleShape homeButton(sf::Vector2f(150.f, 50.f));
    homeButton.setFillColor(sf::Color::Red);
    homeButton.setPosition(1300.f, 900.f);

    sf::Text homeButtonText;
    homeButtonText.setFont(font);
    homeButtonText.setCharacterSize(20);
    homeButtonText.setFillColor(sf::Color::White);
    homeButtonText.setString("Home");
    homeButtonText.setPosition(1340.f, 910.f);

    sf::RectangleShape replayButton(sf::Vector2f(150.f, 50.f));
    replayButton.setFillColor(sf::Color::Green);
    replayButton.setPosition(1100.f, 900.f);

    sf::Text replayButtonText;
    replayButtonText.setFont(font);
    replayButtonText.setCharacterSize(20);
    replayButtonText.setFillColor(sf::Color::White);
    replayButtonText.setString("Play Again");
    replayButtonText.setPosition(1130.f, 910.f);

    sf::Texture image;
    if (!image.loadFromFile("C:/HCMUS/vspoker/poker_start_menu.jpg"))
    {
        cout << "cannot load file";
        return -1;
    }
    sf::Sprite start_menu(image);
    start_menu.setScale(0.5, 0.5);

    sf::Texture Button_mode_1;
    if (!Button_mode_1.loadFromFile("C:/HCMUS/vspoker/mode1.png"))
    {
        cout << " cannot open file button ";
        return -1;
    }

    sf::Sprite button_mode_1(Button_mode_1);
    button_mode_1.setPosition(1000.f, 300.f);

    sf::Text basicModeText;
    basicModeText.setFont(font);
    basicModeText.setCharacterSize(60);
    basicModeText.setFillColor(dark_blue);
    basicModeText.setString("Basic");
    basicModeText.setPosition(1090.f, 340.f);  // button 1

    sf::Texture Button_mode_2;
    if (!Button_mode_2.loadFromFile("C:/HCMUS/vspoker/mode3.png"))
    {
        cout << " cannot open file button ";
        return -1;
    }

    sf::Sprite button_mode_2(Button_mode_2);
    button_mode_2.setPosition(1000.f, 500.f);

    sf::Texture Button_mode_3;
    if (!Button_mode_3.loadFromFile("C:/HCMUS/vspoker/mode1.png"))
    {
        cout << " cannot open file button ";
        return -1;
    }

    sf::Sprite button_mode_3(Button_mode_3);
    button_mode_3.setPosition(1000.f, 700.f);

    sf::Text pick_mode;
    pick_mode.setFont(font);
    pick_mode.setFillColor(customColor);
    pick_mode.setPosition(1000.f, 100.f);
    pick_mode.setCharacterSize(80);
    pick_mode.setString("Choose Modes: ");
    pick_mode.setOutlineThickness(5.0f);  // Add outline thickness
    pick_mode.setOutlineColor(dark_blue);  // Use the dark blue color


    std::string inputString = "";
    bool isEnteringPlayers = false;
    bool isGameStarted = false;
    int number_player = 0;
    std::vector<std::string> store_name;
    std::string result;
    int currentPlayer = 0;
    bool checkButton = false;
    bool gameplay = false;
    bool check_register = false;

    string suits[] = { "hearts", "diamonds", "clubs", "spades" };
    string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king", "ace" };
    Card deck[52];

    sf::Music music_entry;
    if (!music_entry.openFromFile("C:/HCMUS/vspoker/sound_effect/game-music-loop-7-145285.mp3")) {
        cout << "cannot load music";
        return -1;
    }

    music_entry.play();

    sf::SoundBuffer choosing_mode;
    if (!choosing_mode.loadFromFile("C:/HCMUS/vspoker/sound_effect/game-start-6104.mp3")) {
        cout << " cannot load sound entry";
        return -1;
    }

    sf::Sound mode_chosing_sound(choosing_mode);

    sf::SoundBuffer press_button;
    if (!press_button.loadFromFile("C:/HCMUS/vspoker/sound_effect/pop-sound-effect-197846.mp3")) {
        cout << " cannot load sound entry";
        return -1;
    }

    sf::Sound press_button_sound(press_button);

    sf::SoundBuffer press_button_play;
    if (!press_button_play.loadFromFile("C:/HCMUS/vspoker/sound_effect/game-bonus-144751.mp3")) {
        cout << " cannot load sound entry";
        return -1;
    }

    sf::Sound press_button_play_sound(press_button_play);

    sf::Music game_mode_1;

    if (!game_mode_1.openFromFile("C:/HCMUS/vspoker/sound_effect/soft-piano-loop-192098.mp3")) {
        cout << "cannot load sound mode 1";
        return -1;
    }


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {   
            cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << endl;

            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }

            if (!isGameStarted)
            {

                if (!check_register)
                {
                    if (event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        sf::Vector2f mousePosFl = window.mapPixelToCoords(mousePos);
                        if (button_mode_1.getGlobalBounds().contains(mousePosFl.x, mousePosFl.y))
                        {
                            check_register = true;
                            mode_chosing_sound.play();  //adding sound when choosing mode
                           
                        }
                    }
                }
                else
                {
                    if (checkButton && event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                            sf::Vector2f mousePosFloat = window.mapPixelToCoords(mousePos);
                            //std::cout << "Mouse clicked at: " << mousePosFloat.x << ", " << mousePosFloat.y << std::endl;
                            if (playButton.getGlobalBounds().contains(mousePosFloat.x, mousePosFloat.y))
                            {
                                isGameStarted = true;
                                gameplay = true;
                                std::cout << "change type" << std::endl;
                                press_button_play_sound.play();
                                music_entry.stop();
                                game_mode_1.play();
                            }
                        }
                    }
                    if (event.type == sf::Event::TextEntered)
                    {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && !inputString.empty())
                        { // Backspace
                            inputString.pop_back();
                        }
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                        { // Enter key
                            if (!isEnteringPlayers)
                            { // entering number of player 1 time
                                if (!inputString.empty())
                                {
                                    number_player = stoi(inputString);
                                    isEnteringPlayers = true;                                                        // checkpoint never turn to this again
                                    promptText.setString("Enter player name " + to_string(currentPlayer + 1) + ":"); // change the promptest to enter player name
                                    inputString.clear();
                                }
                                // store the number of player
                            }
                            else
                            {
                                store_name.push_back(inputString);
                                inputString.clear();
                                currentPlayer++;
                                if (currentPlayer < number_player)
                                {
                                    promptText.setString("Enter player name " + to_string(currentPlayer + 1) + ":");
                                }
                                else
                                {
                                    promptText.setString("Click 'Play' to start the game");
                                    checkButton = true;
                                }
                            }
                        }
                        else if (!checkButton && event.text.unicode < 128)
                        { // enter text
                            inputString += (char)(event.text.unicode);
                        }
                    }
                }
            }
        }

        window.clear();

        if (!isGameStarted)
        {
            // after start menu;
            if (check_register)
            {
                inputText.setString(inputString); // update test after typing
                window.draw(promptText);
                window.draw(inputText);
                if (checkButton)
                {
                    window.draw(playButton);
                    window.draw(playButtonText);
                }
            }
            else
            {   
                window.draw(pick_mode);
                window.draw(button_mode_1);
                window.draw(basicModeText);
                window.draw(button_mode_2);
                window.draw(button_mode_3);
                window.draw(start_menu);
            }
        }

        else if (gameplay)
        {
            int index = 0;
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 13; ++j)
                {
                    deck[index].suit = suits[i];
                    deck[index].rank = ranks[j];
                    ++index;
                }
            }
            shuffle_cards(deck, 52);
            vector<pair<string, string>> card_store{};

            Hand* players = dealing_cards(deck, number_player);
            auto winner_info = get_winner(players, number_player);
            int winner_pos = winner_info.first;
            int winner_strength = winner_info.second;

            bool wintype;

            for (int i = 0; i < number_player; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    card_store.push_back({ players[i].cards[j].rank, players[i].cards[j].suit }); // store hand of each people for displaying it
                }

                wintype = false;
                if ((i + 1) == winner_pos)
                {
                    wintype = true;
                }
                else if (winner_pos == 0)
                {
                    wintype = true;
                }
                update_player_data(store_name[i], wintype, winner_strength);
                update_playerlist(store_name[i], get_win_rate(store_name[i]));
            }

            sf::Texture textureTheme;
            if (!textureTheme.loadFromFile("C:/HCMUS/vspoker/pokertheme.png"))
            {
                cout << "cannot open file" << endl;
            }

            sf::Sprite background;
            background.setTexture(textureTheme);
            background.setPosition(0.f, 0.f);
            sf::Vector2u textureSize = textureTheme.getSize();
            float scaleX = 1600.f / textureSize.x;
            float scaleY = 1000.f / textureSize.y;
            background.setScale(scaleX, scaleY);

            window.draw(background);

            /*
             * make a vector to store each of players'hand cards, and after that display each 5 card together in the board.
             * And make a algorithm to display player card side by side, maximum 4 edges
             * And rotate the card if the edge is left, right or top.
             * https://www.sfml-dev.org/tutorials/2.6/graphics-transform.php this link for rotating
             */

            int cnt = 0;
            float cardSpacing = 30.f; // Khoảng cách giữa các lá bài
            float rowSpacing = 200.f; // Khoảng cách giữa các hàng
            int cardsPerRow = 5;
            int totalRows = 4;
            int posStoreName = 0;

            for (int i = 0; i < card_store.size(); i++)
            {
                string textFile = "C:/HCMUS/vspoker/cardpacks/" + card_store[i].first + "_of_" + card_store[i].second + ".png";
                sf::Texture card_pick;
                if (!card_pick.loadFromFile(textFile))
                {
                    cout << "Failed to load file: " << textFile << endl;
                    continue;
                }
                sf::Sprite card_display(card_pick);
                card_display.setScale(0.25, 0.25); // 125 x 181.5

                int row = i / cardsPerRow;
                int col = i % cardsPerRow;

                // Đặt vị trí cho lá bài
                float posX = 490 + (125 + cardSpacing) * col;
                float posY = 100 + row * rowSpacing;

                card_display.setPosition(posX, posY);
                card_display.setRotation(0.f);

                // tạo các dòng chữ để chỉ người chơi ở từng dòng
                if (i % 5 == 0)
                {
                    sf::Text Name;
                    Name.setFont(font);
                    Name.setFillColor(sf::Color::Red);
                    Name.setPosition(300, posY);
                    Name.setCharacterSize(24);
                    Name.setString("Player: " + store_name[posStoreName++]);
                    window.draw(Name);
                }
                window.draw(card_display);
            }

            if (winner_pos == 0)
            {
                result = "TIE!";
            }
            else
            {
                result = "Player " + to_string(winner_pos) + " wins with hand strength: " + type_of_card(winner_strength);
            }

            sf::Text resultText;
            resultText.setFont(font);
            resultText.setCharacterSize(30);
            resultText.setFillColor(sf::Color::Red);
            resultText.setString(result);
            resultText.setPosition(0.f, 0.f);

            sf::Text text;
            text.setFont(font);
            text.setPosition(0.f, 50.f);
            text.setCharacterSize(30);
            text.setFillColor(sf::Color::Yellow);
            text.setString("PRESS ENTER FOR PLAYING AGAIN");

            window.draw(resultText);
            window.draw(text);
            window.draw(homeButton);
            window.draw(homeButtonText);
            window.draw(replayButton);
            window.draw(replayButtonText);
            window.display();

            bool waitingForInput = true;
            while (waitingForInput)
            {
                sf::Event event;
                while (window.pollEvent(event))
                {

                    if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    {
                        window.close();
                        waitingForInput = false;
                    }
                    if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                            sf::Vector2f mousePosFloat = window.mapPixelToCoords(mousePos);
                            // std::cout << "Mouse clicked at: " << mousePosFloat.x << ", " << mousePosFloat.y << std::endl;
                            if (homeButton.getGlobalBounds().contains(mousePosFloat.x, mousePosFloat.y))
                            {
                                waitingForInput = false;
                                isGameStarted = false;
                                checkButton = false;
                                gameplay = false;
                                isEnteringPlayers = false;

                                check_register = false; //return home page

                                currentPlayer = 0;
                                number_player = 0;
                                store_name.clear();
                                promptText.setString("Enter the number of players:");

                                game_mode_1.stop();
                                press_button_sound.play();
                                music_entry.play();
                            }
                            if (replayButton.getGlobalBounds().contains(mousePosFloat.x, mousePosFloat.y))
                            {
                                waitingForInput = false;
                                isGameStarted = false;
                                checkButton = false;
                                gameplay = false;
                                isEnteringPlayers = false;
                                currentPlayer = 0;
                                number_player = 0;
                                store_name.clear();
                                promptText.setString("Enter the number of players:");

                                game_mode_1.stop();
                                press_button_sound.play();
                                music_entry.play();
                            }
                        }
                    }
                }
            }
        }

        window.display();
    }

    return 0;
}

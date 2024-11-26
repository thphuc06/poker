#include "fullDeclare.h"
#include "fullDeclare2.h"
#include "fullDeclare3.h"
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

 // enum game_state {
 //     start,
 //     sign,
 //     mode1,
 //     mode2,
 //     mode3,
 //     mode4
 // };

enum TexasHoldemStage
{
    FOLDING,
    FLOP,
    TURN,
    RIVER,
    SHOWDOWN
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 1000), "GamePoker");
    window.setFramerateLimit(60);

    sf::Color customColor(184, 134, 11); // gold color
    sf::Color dark_blue(0, 70, 140);     // blue font

    sf::Font font;
    if (!font.loadFromFile("textFont/arial.ttf"))
    {
        return -1;
    }

    // register section

    sf::Texture register_background;
    if (!register_background.loadFromFile("assets/register_background.jpg"))
    {
        cout << "cannot open background";
        return -1;
    }

    sf::Sprite register_theme(register_background);
    /*register_theme.setScale(0.5, 0.5);*/

    sf::Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(34);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(1100.f, 235.f);

    sf::Text promptText;
    promptText.setFont(font);
    promptText.setCharacterSize(50);
    promptText.setFillColor(sf::Color::Yellow);
    promptText.setPosition(940.f, 110.f);
    promptText.setString("Enter the number of players:");
    promptText.setOutlineColor(sf::Color::Black);
    promptText.setOutlineThickness(2.f);

    sf::RectangleShape playButton(sf::Vector2f(200.f, 70.f));
    playButton.setFillColor(sf::Color(100, 200, 255));
    playButton.setOutlineColor(sf::Color(0, 128, 255));
    playButton.setOutlineThickness(5.f);
    playButton.setPosition(1200.f, 600.f);

    // Văn bản trên nút
    sf::Text playButtonText;
    playButtonText.setFont(font);
    playButtonText.setCharacterSize(40); // Tăng kích thước chữ
    playButtonText.setFillColor(sf::Color::White);
    playButtonText.setString("Play");
    playButtonText.setOutlineColor(sf::Color::Black); // Viền đen cho chữ
    playButtonText.setOutlineThickness(2.f);
    playButtonText.setPosition(1257.f, 613.f);

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
    if (!image.loadFromFile("assets/poker_start_menu.jpg"))
    {
        cout << "cannot load file";
        return -1;
    }
    sf::Sprite start_menu(image);
    start_menu.setScale(0.5, 0.5);

    sf::Texture Button_mode_1;
    if (!Button_mode_1.loadFromFile("assets/mode1.png"))
    {
        cout << " cannot open file button ";
        return -1;
    }

    sf::Sprite button_mode_1(Button_mode_1);
    button_mode_1.setPosition(1000.f, 220.f);

    sf::Text basicModeText;
    basicModeText.setFont(font);
    basicModeText.setCharacterSize(60);
    basicModeText.setFillColor(dark_blue);
    basicModeText.setString("Basic");
    basicModeText.setPosition(1090.f, 260.f); // button 1

    // mode 2: three card hand ("bai cao")
    sf::Texture Button_mode_2;
    if (!Button_mode_2.loadFromFile("assets/mode3.png"))
    {
        cout << " cannot open file button ";
        return -1;
    }

    sf::Sprite button_mode_2(Button_mode_2);
    button_mode_2.setPosition(1000.f, 380.f);

    sf::Text ThreeCardModeText;
    ThreeCardModeText.setFont(font);
    ThreeCardModeText.setCharacterSize(50);
    ThreeCardModeText.setFillColor(dark_blue);
    ThreeCardModeText.setString("Three cards");
    ThreeCardModeText.setPosition(1020.f, 427.f);

    sf::Texture Button_mode_3;
    if (!Button_mode_3.loadFromFile("assets/mode1.png"))
    {
        cout << " cannot open file button ";
        return -1;
    }

    sf::Sprite button_mode_3(Button_mode_3);
    button_mode_3.setPosition(1000.f, 545.f);

    sf::Text HoldemPokerText;
    HoldemPokerText.setFont(font);
    HoldemPokerText.setCharacterSize(45);
    HoldemPokerText.setFillColor(dark_blue);
    HoldemPokerText.setString("Hold'em Poker");
    HoldemPokerText.setPosition(1020.f, 592.f);

    sf::Texture Button_mode_4;
    if (!Button_mode_4.loadFromFile("assets/mode3.png"))
    {
        cout << " cannot open file button ";
        return -1;
    }

    sf::Sprite button_mode_4(Button_mode_4);
    button_mode_4.setPosition(1000.f, 705.f);

    sf::Text pick_mode;
    pick_mode.setFont(font);
    pick_mode.setFillColor(customColor);
    pick_mode.setPosition(1000.f, 100.f);
    pick_mode.setCharacterSize(80);
    pick_mode.setString("Choose Modes: ");
    pick_mode.setOutlineThickness(5.0f);  // Add outline thickness
    pick_mode.setOutlineColor(dark_blue); // Use the dark blue color

    // leaderboard
    sf::RectangleShape leaderboard(sf::Vector2f(300, 50));
    leaderboard.setPosition(1050, 900);
    leaderboard.setFillColor(sf::Color(135, 206, 235));  // Màu xanh dương nhạt
    leaderboard.setOutlineColor(sf::Color(255, 191, 0)); // Màu vàng ngả cam
    leaderboard.setOutlineThickness(5.f);                // Độ dày viền ngoài

    sf::Text leaderboard_text;
    leaderboard_text.setFont(font);
    leaderboard_text.setFillColor(sf::Color(0, 51, 102));
    leaderboard_text.setPosition(1105.f, 905.f);
    leaderboard_text.setCharacterSize(32);
    leaderboard_text.setString("Leader Board");
    leaderboard_text.setOutlineColor(sf::Color(255, 165, 0));
    leaderboard_text.setOutlineThickness(1.0f);

    sf::Texture leaderboard_image;
    if (!leaderboard_image.loadFromFile("assets/leaderboard_image.png"))
    {
        cout << " cannot load image";
        return -1;
    }

    sf::Sprite leaderboard_background(leaderboard_image);
    leaderboard_background.setScale(1.5, 1.5);
    leaderboard_background.setPosition(0, 0); // 260 for middle

    sf::RectangleShape green_background_leaderboard(sf::Vector2f(1600, 1000));
    green_background_leaderboard.setFillColor(sf::Color(50, 180, 100));

    // make a return button
    sf::RectangleShape button_return(sf::Vector2f(210, 50));
    button_return.setPosition(1350, 930);
    button_return.setFillColor(sf::Color::Black);
    button_return.setOutlineColor(sf::Color(161, 24, 14));
    button_return.setOutlineThickness(3.0);
    // return in leaderboard 2
    sf::RectangleShape button_return1(sf::Vector2f(210, 50));
    button_return1.setPosition(1350, 930);
    button_return1.setFillColor(sf::Color::Black);
    button_return1.setOutlineColor(sf::Color(161, 24, 14));
    button_return1.setOutlineThickness(3.0);

    // make a text return
    sf::Text leaderboard_return;
    leaderboard_return.setFont(font);
    leaderboard_return.setPosition(1375, 935);
    leaderboard_return.setCharacterSize(27);
    leaderboard_return.setFillColor(sf::Color(50, 180, 100));
    leaderboard_return.setString("Return menu");

    // leaderboard win game background
    sf::Texture leaderboard_win;
    if (!leaderboard_win.loadFromFile("assets/leaderboard_win.png"))
    {
        cout << "cannot load file";
        return -1;
    }

    sf::Sprite leaderboard_wingame(leaderboard_win);
    leaderboard_wingame.setScale(1.5, 1.5);
    leaderboard_wingame.setPosition(-100, 0);

    // change leaderboard button
    sf::RectangleShape button_change_leaderboard(sf::Vector2f(210, 50));
    button_change_leaderboard.setPosition(1350, 865);
    button_change_leaderboard.setFillColor(sf::Color::Black);
    button_change_leaderboard.setOutlineColor(sf::Color(161, 24, 14));
    button_change_leaderboard.setOutlineThickness(3.0);

    // change leaderboard text
    sf::Text leaderboard_2;
    leaderboard_2.setFont(font);
    leaderboard_2.setPosition(1375, 870);
    leaderboard_2.setCharacterSize(27);
    leaderboard_2.setFillColor(sf::Color(50, 180, 100));
    leaderboard_2.setString("Change type");

    sf::RectangleShape favorite_card(sf::Vector2f(300, 60));
    favorite_card.setPosition(1260, 160);
    favorite_card.setFillColor(sf::Color::Black);
    favorite_card.setOutlineColor(sf::Color(161, 24, 14));
    favorite_card.setOutlineThickness(6.0);

    sf::Text favorite_card_text;
    favorite_card_text.setFont(font);
    favorite_card_text.setPosition(1275, 165);
    favorite_card_text.setCharacterSize(35);
    favorite_card_text.setFillColor(sf::Color::Red);
    favorite_card_text.setString("Favorite card win");

    // track player profile button
    sf::RectangleShape profile_search_button(sf::Vector2f(350, 50));
    profile_search_button.setFillColor(sf::Color::Red);
    profile_search_button.setPosition(1095, 115);

    sf::Text search_profile_prompt;
    search_profile_prompt.setFont(font);
    search_profile_prompt.setPosition(1110, 120);
    search_profile_prompt.setCharacterSize(30);
    search_profile_prompt.setFillColor(sf::Color::Black);
    search_profile_prompt.setString("Click for typing name");

    sf::Text search_typing_text; // text update when typing name;
    search_typing_text.setFont(font);
    search_typing_text.setCharacterSize(30);
    search_typing_text.setPosition(1130, 210);

    sf::Text player_profile_track;
    player_profile_track.setFont(font);
    player_profile_track.setCharacterSize(30);
    player_profile_track.setPosition(1130, 300);

    sf::Text not_exist_profile;
    not_exist_profile.setFont(font);
    not_exist_profile.setCharacterSize(30);
    not_exist_profile.setPosition(1130, 300);
    not_exist_profile.setString("not exist");

    // flag for typing player name
    bool isTypingPlayer = false;
    string search_name = ""; // this will store player name for display;
    bool display_player_profile = false;

    // initializing flag for changing window
    bool checkButton = false;
    bool gameplay = false;
    bool check_register = false;
    bool check_leaderboard = false;
    bool check_change_leaderboard = false;
    bool mode1_check = false;
    bool mode2_check = false;
    bool mode3_check = false;

    /*
     * initializing for mode 1
     */

    string inputString = "";
    bool isEnteringPlayers = false;
    bool isGameStarted = false;
    int number_player = 0;
    vector<string> store_name;
    string result;
    int currentPlayer = 0;

    vector<string>suits = { "hearts", "diamonds", "clubs", "spades" };
    vector<string>ranks = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king", "ace" };
    Card* deck = new Card[52];


    sf::Texture textureTheme;
    if (!textureTheme.loadFromFile("assets/pokertheme.png"))
    {
        cout << "cannot open file" << endl;
        return -1;
    }

    // background game basic
    sf::Sprite background(textureTheme);
    background.setPosition(0.f, 0.f);
    sf::Vector2u textureSize = textureTheme.getSize();
    float scaleX = 1600.f / textureSize.x;
    float scaleY = 1000.f / textureSize.y;
    background.setScale(scaleX, scaleY);

    // background
    sf::Texture background_poker;
    if (!background_poker.loadFromFile("assets/poker_table_background.jpg"))
    {
        return -1;
    }

    sf::Sprite background_holdem(background_poker);

    // poker_back_card texture
    sf::Texture poker_back;
    if (!poker_back.loadFromFile("cardpacks/poker_back.png"))
    {
        return -1;
    }

    sf::Sprite poker_back_card(poker_back);
    poker_back_card.setScale(0.3, 0.3);

    // initialize for mode 2
    int number_player_2 = 0;

    // initialize for mode 3
    vector<bool> activePlayers = { true, true, true }; // checking if they fold or not
    TexasHoldemStage holdemStage = FOLDING;
    int current_player = 0; // for counting player opt
    bool needPlayerPrompt = true;
    bool isAgain = true;
    vector<vector<Card3>> playerHands; // remember to reset each game
    Hand3 communityCards;
    bool waitingForNextClick = true;

    //
    sf::Text fold_or_not;
    fold_or_not.setFont(font);
    fold_or_not.setCharacterSize(50);
    fold_or_not.setPosition(350, 50);
    fold_or_not.setFillColor(sf::Color::Red);

    sf::RectangleShape opt1(sf::Vector2f(200, 80));
    opt1.setFillColor(sf::Color::Black);
    opt1.setPosition(560, 130);

    sf::RectangleShape opt2(sf::Vector2f(200, 80));
    opt2.setFillColor(sf::Color::Black);
    opt2.setPosition(790, 130);

    sf::Text opt1_text;
    opt1_text.setFont(font);
    opt1_text.setCharacterSize(45);
    opt1_text.setFillColor(sf::Color::Red);
    opt1_text.setPosition(610, 140);
    opt1_text.setString("YES");

    sf::Text opt2_text;
    opt2_text.setFont(font);
    opt2_text.setCharacterSize(45);
    opt2_text.setFillColor(sf::Color::Red);
    opt2_text.setPosition(855, 140);
    opt2_text.setString("NO");

    /*
     * music and sound operation
     */

    sf::Music music_entry;
    if (!music_entry.openFromFile("sound_effect/game-music-loop-7-145285.mp3"))
    {
        cout << "cannot load music";
        return -1;
    }

    music_entry.play();

    sf::SoundBuffer choosing_mode;
    if (!choosing_mode.loadFromFile("sound_effect/game-start-6104.mp3"))
    {
        cout << " cannot load sound entry";
        return -1;
    }

    sf::Sound mode_chosing_sound(choosing_mode);

    sf::SoundBuffer press_button;
    if (!press_button.loadFromFile("sound_effect/pop-sound-effect-197846.mp3"))
    {
        cout << " cannot load sound entry";
        return -1;
    }

    sf::Sound press_button_sound(press_button);

    sf::SoundBuffer press_button_play;
    if (!press_button_play.loadFromFile("sound_effect/game-bonus-144751.mp3"))
    {
        cout << " cannot load sound entry";
        return -1;
    }

    sf::Sound press_button_play_sound(press_button_play);



    sf::Music game_mode_1;
    if (!game_mode_1.openFromFile("sound_effect/soft-piano-loop-192098.mp3"))
    {
        cout << "cannot load sound mode 1";
        return -1;
    }

    //music holdem 
    sf::Music game_mode_3;
    if (!game_mode_3.openFromFile("sound_effect/game-music-loop-6-144641.mp3")) {
        cout << "cannot open music";
        return -1;
    }

    sf::Music game_mode_leadership;
    if (!game_mode_leadership.openFromFile("sound_effect/game-music-loop-3-144252.mp3")) {
        cout << "cannot open music";
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
                if (!check_register && !check_change_leaderboard)
                {
                    if (event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        sf::Vector2f mousePosFl = window.mapPixelToCoords(mousePos);
                        if (button_mode_1.getGlobalBounds().contains(mousePosFl.x, mousePosFl.y))
                        {
                            check_register = true;
                            check_leaderboard = false;
                            check_change_leaderboard = false;
                            mode1_check = true;
                            mode_chosing_sound.play(); // adding sound when choosing mode
                        }
                    }
                    if (event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        sf::Vector2f mousePosFl = window.mapPixelToCoords(mousePos);
                        if (leaderboard.getGlobalBounds().contains(mousePosFl.x, mousePosFl.y))
                        {
                            check_leaderboard = true;
                            check_change_leaderboard = false;
                            check_register = true;
                            display_player_profile = false;
                            isTypingPlayer = false;

                            music_entry.stop();
                            game_mode_leadership.play();
                            continue;
                        }
                    }
                    if (event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        sf::Vector2f mousePosFl = window.mapPixelToCoords(mousePos);
                        if (button_mode_2.getGlobalBounds().contains(mousePosFl.x, mousePosFl.y))
                        {
                            mode2_check = true;
                            check_register = true;
                            mode_chosing_sound.play();
                            continue;
                        }
                    }
                    if (event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        sf::Vector2f mousePosFl = window.mapPixelToCoords(mousePos);
                        if (button_mode_3.getGlobalBounds().contains(mousePosFl.x, mousePosFl.y))
                        {
                            mode3_check = true;
                            /*check_register = true;*/
                            gameplay = true;
                            isGameStarted = true;
                            music_entry.stop();
                            game_mode_3.play();
                            mode_chosing_sound.play();
                            continue;
                        }
                    }
                }
                else if (check_leaderboard)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePosFl = window.mapPixelToCoords(mousePos);

                    if (event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (button_return.getGlobalBounds().contains(mousePosFl.x, mousePosFl.y))
                        {
                            cout << "RETURN CLICK";
                            check_register = false;
                            check_leaderboard = false;

                            game_mode_leadership.stop();
                            music_entry.play();
                        }
                    }
                    if (event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (button_change_leaderboard.getGlobalBounds().contains(mousePosFl.x, mousePosFl.y))
                        {
                            check_register = false;
                            check_change_leaderboard = true;
                            check_leaderboard = false;
                        }
                    }
                    if (event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (profile_search_button.getGlobalBounds().contains(mousePosFl.x, mousePosFl.y))
                        {
                            isTypingPlayer = true;
                            display_player_profile = false;
                            press_button_sound.play();
                        }
                    }
                    if (isTypingPlayer)
                    {
                        if (event.type == sf::Event::TextEntered)
                        {
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && !inputString.empty())
                            {
                                inputString.pop_back();
                            }
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                            {
                                search_name = inputString;
                                isTypingPlayer = false;
                                display_player_profile = true;
                                inputString.clear();
                            }
                            else if (!checkButton && event.text.unicode < 128)
                            { // enter text
                                inputString += (char)(event.text.unicode);
                            }
                        }
                        search_typing_text.setString(inputString);
                    }
                }
                else if (check_change_leaderboard)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePosFl = window.mapPixelToCoords(mousePos);
                    // get a button to return home
                    cout << "hi";
                    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (button_return1.getGlobalBounds().contains(mousePosFl.x, mousePosFl.y))
                        {
                            cout << "CLICKED";
                            check_register = false;
                            check_leaderboard = false;
                            check_change_leaderboard = false;
                            game_mode_leadership.stop();
                            music_entry.play();
                        }
                    }
                }
                else
                {
                    if (checkButton && event.type == sf::Event::MouseButtonPressed && mode1_check)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                            sf::Vector2f mousePosFloat = window.mapPixelToCoords(mousePos);
                            // std::cout << "Mouse clicked at: " << mousePosFloat.x << ", " << mousePosFloat.y << std::endl;
                            if (playButton.getGlobalBounds().contains(mousePosFloat.x, mousePosFloat.y))
                            {
                                isGameStarted = true;
                                gameplay = true;
                                // std::cout << "change type" << std::endl;
                                press_button_play_sound.play();
                                music_entry.stop();
                                game_mode_1.play();
                            }
                        }
                    }
                    if (event.type == sf::Event::TextEntered && mode1_check)
                    {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && !inputString.empty())
                        { // Backspace
                            inputString.pop_back();
                        }
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                        { // Enter key
                            if (!isEnteringPlayers)
                            { // entering number of player 1 time
                                if (!inputString.empty() && stoi(inputString) >= 2 && stoi(inputString) <= 4 )
                                {
                                    number_player = stoi(inputString);
                                    isEnteringPlayers = true;                                                        // checkpoint never turn to this again
                                    promptText.setString("Enter player name " + to_string(currentPlayer + 1) + ":"); // change the promptest to enter player name
                                    inputString.clear();
                                }
                                inputString.clear();
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
                    if (event.type == sf::Event::TextEntered && mode2_check)
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
                                    if (stoi(inputString) >= 2 && stoi(inputString) <= 6) {
                                        number_player_2 = stoi(inputString);
                                        checkButton = true;
                                        isEnteringPlayers = true;
                                        promptText.setString("Click 'Play' to start the game");
                                    }

                                    inputString.clear();
                                }
                            }
                        }
                        else if (!checkButton && event.text.unicode < 128)
                        { // enter text
                            inputString += (char)(event.text.unicode);
                        }
                    }
                    if (checkButton && event.type == sf::Event::MouseButtonPressed && mode2_check)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                            sf::Vector2f mousePosFloat = window.mapPixelToCoords(mousePos);
                            if (playButton.getGlobalBounds().contains(mousePosFloat.x, mousePosFloat.y))
                            {
                                isGameStarted = true;
                                gameplay = true;

                                press_button_play_sound.play();
                                music_entry.stop();
                                game_mode_1.play();
                            }
                        }
                    }
                }
            }
        }

        window.clear();

        if (!isGameStarted)
        {
            // after start menu;
            if (mode2_check)
            {
                // draw the background for asking player to pick 2->6 people to play
                // draw a button to start playing
                // after click at the button isGameStarted = true
                // and get the flag mode2_gamplay = true;
                // update return home and play again for mode 2
                window.draw(register_theme);
                inputText.setString(inputString); // update test after typing
                window.draw(promptText);
                window.draw(inputText);
                window.draw(playButton);
                window.draw(playButtonText);
            }
            else if (check_register && !check_leaderboard && mode1_check)
            {
                window.draw(register_theme);
                inputText.setString(inputString); // update test after typing
                window.draw(promptText);
                window.draw(inputText);
                if (checkButton)
                {
                    window.draw(playButton);
                    window.draw(playButtonText);
                }
            }
            else if (!check_register && !check_change_leaderboard)
            {
                window.draw(start_menu);
                window.draw(pick_mode);
                window.draw(button_mode_1);
                window.draw(basicModeText);
                window.draw(button_mode_2);
                window.draw(ThreeCardModeText);
                window.draw(button_mode_3);
                window.draw(HoldemPokerText);
                window.draw(button_mode_4);
                window.draw(leaderboard);
                window.draw(leaderboard_text);
            }
            else if (check_leaderboard && !check_change_leaderboard)
            {
                window.draw(green_background_leaderboard);
                window.draw(leaderboard_background);
                window.draw(button_return);
                window.draw(leaderboard_return);

                window.draw(profile_search_button);
                window.draw(search_profile_prompt);
                window.draw(search_typing_text);
                if (display_player_profile)
                {
                    // display name_winrate_wingame_fav card win
                    // if name didn't exist in the file output "Not exist"
                    // else cout the details of player
                    string player_profile_path = "userprofile/player_" + search_name + ".txt";
                    ifstream file_in(player_profile_path);

                    string gameplay = "0";
                    string gamewin = "0";
                    string winrate = "0";
                    string fav_card = "0";

                    if (file_in)
                    {
                        file_in >> gameplay;
                        file_in >> gamewin;
                        file_in >> fav_card;
                        fav_card = type_of_card(stoi(fav_card));
                        winrate = to_string(get_win_rate(search_name));
                        player_profile_track.setString("name: " + search_name + '\n' + "game played: " + gameplay + '\n' + "game win: " + gamewin + '\n' + "favorite card: " + fav_card + '\n' + "win rate: " + winrate + "%");
                        window.draw(player_profile_track);
                    }
                    else
                    {
                        window.draw(not_exist_profile); // text "not exist"
                    }
                }

                window.draw(button_change_leaderboard);
                window.draw(leaderboard_2);

                ifstream file_in("Leaderboard/leaderboard.txt");
                string s;

                sf::Text player_tier;
                player_tier.setFont(font);
                player_tier.setFillColor(sf::Color::Black);
                player_tier.setCharacterSize(50);

                sf::Text player_score;
                player_score.setFont(font);
                player_score.setFillColor(sf::Color::Black);
                player_score.setCharacterSize(50);

                // spacing
                int block_spacing = 10;
                int character_spacing = 105;
                int step = 0;

                if (file_in)
                {
                    while (getline(file_in, s))
                    {
                        if (step == 5)
                        {
                            break;
                        }
                        stringstream ss(s);
                        string name_top;
                        string score_top;
                        getline(ss, name_top, '-');
                        ss >> score_top;

                        // player_tier.setString(name_top + "                      " + score_top);
                        // player_tier.setPosition(630, 320 + (block_spacing + character_spacing) * step);

                        player_tier.setString(name_top);
                        player_score.setString(score_top);

                        player_tier.setPosition(370, 320 + (block_spacing + character_spacing) * step);
                        player_score.setPosition(800, 320 + (block_spacing + character_spacing) * step);

                        window.draw(player_score);
                        window.draw(player_tier);
                        step++;
                    }
                    file_in.close();
                }
            }
            else if (check_change_leaderboard)
            {
                window.draw(leaderboard_wingame);
                window.draw(favorite_card);
                window.draw(favorite_card_text);
                window.draw(button_return1);
                window.draw(leaderboard_return);

                // display player top info
                ifstream file_in("Leaderboard/leaderboard_win_rate.txt");
                string s;

                sf::Text player_tier;
                player_tier.setFont(font);
                player_tier.setFillColor(sf::Color::Black);
                player_tier.setCharacterSize(50);

                sf::Text player_score;
                player_score.setFont(font);
                player_score.setFillColor(sf::Color::Black);
                player_score.setCharacterSize(50);

                sf::Text player_fav;
                player_fav.setFont(font);
                player_fav.setFillColor(sf::Color::Red);
                player_fav.setCharacterSize(50);
                player_fav.setStyle(sf::Text::Underlined);
                player_fav.setOutlineColor(sf::Color(0, 0, 128));
                player_fav.setOutlineThickness(3.0);

                // spacing
                int block_spacing = 12;
                int character_spacing = 105;
                int step = 0;

                if (file_in)
                {
                    while (getline(file_in, s))
                    {
                        if (step == 5)
                        {
                            break;
                        }
                        stringstream ss(s);
                        string name_top;
                        string score_top;
                        getline(ss, name_top, '-');
                        ss >> score_top;

                        player_tier.setString(name_top);
                        player_score.setString(score_top);

                        player_tier.setPosition(600, 300 + (block_spacing + character_spacing) * step);
                        player_score.setPosition(1030, 300 + (block_spacing + character_spacing) * step);

                        string profile_path = "userprofile/player_" + name_top + ".txt";
                        ifstream file_in_profile(profile_path);
                        string score = "";
                        if (file_in_profile)
                        {
                            if (stoi(score_top) > 0)
                            {
                                file_in_profile >> score >> score >> score;
                                score = type_of_card(stoi(score)); // get the third element as the most fav card type
                            }
                            else
                            {
                                score = '0';
                            }
                            player_fav.setString(score);
                            player_fav.setPosition(1280, 300 + (block_spacing + character_spacing) * step);
                            window.draw(player_fav);
                        }
                        else
                        {
                            cout << "cannot open player profile";
                        }

                        window.draw(player_score);
                        window.draw(player_tier);
                        step++;
                    }
                    file_in.close();
                }

                // display player top info of fav card win

                ifstream file_in_new("Leaderboard/leaderboard_win_rate.txt");
                string name;

                // get the first name in the file and track it in the player profile
                // file name is: userprofile/ + player_ + name
            }
        }

        else if (gameplay)
        {
            if (mode3_check)
            {   
                window.draw(background_holdem);

                // Create and shuffle deck
                // game logic

                // stage the flop
                // stage the turn
                // stage the river

                // show community card for each stage

                if (holdemStage == FOLDING)
                {
                    if (isAgain)
                    {
                        vector<Card3> deck = makeDeck();
                        shuffle(deck);

                        // Deal 2 cards to each player (6 cards total)
                        /*vector<vector<Card3>> playerHands;*/ // use this for futher comparison

                        for (int i = 0; i < 3; i++)
                        {
                            playerHands.push_back(drawcard(deck, 2));
                        }

                        // Deal 5 community cards
                        communityCards = drawcard(deck, 5);

                        isAgain = false; // block
                    }

                    // Display bottom player cards (Player 1)
                    float bottomCardSpacing = 30.f;
                    float cardWidth = 125 * 0.25;    // 125 is the card image width
                    float cardHeight = 181.5 * 0.25; // 181.5 is the card image height

                    for (int i = 0; i < 2; i++)
                    {
                        string textFile = "cardpacks/" + playerHands[0][i].Rank + "_of_" + Suit_name[playerHands[0][i].suit_name] + ".png";
                        sf::Texture card_pick;
                        if (!card_pick.loadFromFile(textFile))
                        {
                            cout << "Failed to load file: " << textFile << endl;
                            continue;
                        }
                        sf::Sprite card_display(card_pick);
                        card_display.setScale(0.3, 0.3);

                        // Position at bottom center
                        float posX = 730 + (cardWidth + bottomCardSpacing) * i;
                        float posY = 740;
                        card_display.setPosition(posX, posY);

                        window.draw(card_display);

                        if (!activePlayers[0])
                        {
                            poker_back_card.setPosition(posX, posY);
                            window.draw(poker_back_card);
                        }
                    }

                    // Display left player cards (Player 2)
                    for (int i = 0; i < 2; i++)
                    {
                        string textFile = "cardpacks/" + playerHands[1][i].Rank + "_of_" + Suit_name[playerHands[1][i].suit_name] + ".png";
                        sf::Texture card_pick;
                        if (!card_pick.loadFromFile(textFile))
                        {
                            cout << "Failed to load file: " << textFile << endl;
                            continue;
                        }
                        sf::Sprite card_display(card_pick);
                        card_display.setScale(0.3, 0.3);

                        // Position at left center
                        float posX = 250;
                        float posY = 440 + (bottomCardSpacing + cardWidth) * i;
                        card_display.setPosition(posX, posY);
                        card_display.setRotation(90); // Rotate cards for left player
                        window.draw(card_display);

                        if (!activePlayers[1])
                        {
                            poker_back_card.setPosition(posX, posY);
                            poker_back_card.setRotation(90);
                            window.draw(poker_back_card);
                        }
                        poker_back_card.setRotation(0); // reset rotation
                    }

                    // Display right player cards (Player 3)
                    for (int i = 0; i < 2; i++)
                    {
                        string textFile = "cardpacks/" + playerHands[2][i].Rank + "_of_" + Suit_name[playerHands[2][i].suit_name] + ".png";
                        sf::Texture card_pick;
                        if (!card_pick.loadFromFile(textFile))
                        {
                            cout << "Failed to load file: " << textFile << endl;
                            continue;
                        }
                        sf::Sprite card_display(card_pick);
                        card_display.setScale(0.3, 0.3);

                        // Position at right center
                        float posX = 1360;
                        float posY = 590 + (cardHeight + bottomCardSpacing) * i;
                        card_display.setPosition(posX, posY);
                        card_display.setRotation(-90); // Rotate cards for right player
                        window.draw(card_display);

                        if (!activePlayers[2])
                        {
                            poker_back_card.setPosition(posX, posY);
                            poker_back_card.setRotation(-90);
                            window.draw(poker_back_card);
                        }
                        poker_back_card.setRotation(0); // reset rotation
                    }

                    // Display community cards in the middle
                    float communityCardSpacing = 30.f;
                    for (int i = 0; i < 5; i++)
                    {
                        string textFile = "cardpacks/" + communityCards[i].Rank + "_of_" + Suit_name[communityCards[i].suit_name] + ".png";
                        sf::Texture card_pick;
                        if (!card_pick.loadFromFile(textFile))
                        {
                            cout << "Failed to load file: " << textFile << endl;
                            continue;
                        }
                        sf::Sprite card_display(card_pick);
                        card_display.setScale(0.3, 0.3);

                        // Position in center of screen
                        float posX = 600 + (cardWidth + bottomCardSpacing) * i;
                        float posY = 300;
                        card_display.setPosition(posX, posY);

                        window.draw(card_display);

                        poker_back_card.setPosition(posX, posY);
                        window.draw(poker_back_card); // hiding card
                    }

                    // Draw player labels
                    sf::Text playerText;
                    playerText.setFont(font);
                    playerText.setCharacterSize(24);
                    playerText.setFillColor(sf::Color::Red);

                    // Bottom player
                    playerText.setString("Player 1");
                    playerText.setPosition(600, 750);
                    window.draw(playerText);

                    // Left player
                    playerText.setString("Player 2");
                    playerText.setPosition(20, 405);
                    window.draw(playerText);

                    // Right player
                    playerText.setString("Player 3");
                    playerText.setPosition(1500, 405);
                    window.draw(playerText);


                    window.draw(opt1);
                    window.draw(opt2);
                    window.draw(opt1_text);
                    window.draw(opt2_text);

                    if (current_player < 3)
                    {
                        // passing who has fold
                        while (current_player < 3 && !activePlayers[current_player])
                        {
                            // std::cout << "Bỏ qua Player " << current_player + 1 << " (đã fold)\n";
                            current_player++;
                        }

                        if (current_player < 3)
                        {
                            fold_or_not.setString("FOLDING: Player " + to_string(current_player + 1) + ", do you want to fold?");
                            window.draw(fold_or_not);

                            if (event.type == sf::Event::MouseButtonPressed &&
                                event.mouseButton.button == sf::Mouse::Left &&
                                waitingForNextClick)
                            { // Chỉ xử lý khi đang đợi click mới

                                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                                sf::Vector2f mousePosFloat = window.mapPixelToCoords(mousePos);

                                std::cout << "Click" << mousePosFloat.x << ", " << mousePosFloat.y << "\n";

                                if (opt1.getGlobalBounds().contains(mousePosFloat))
                                {
                                    // std::cout << "Player " << current_player + 1 << " pick\n";
                                    activePlayers[current_player] = false;
                                    current_player++;
                                    waitingForNextClick = false; // clicking flag to avoid accident redundancy
                                    press_button_sound.play();
                                }
                                else if (opt2.getGlobalBounds().contains(mousePosFloat))
                                {
                                    // std::cout << "Player " << current_player + 1 << " pick\n";
                                    current_player++;
                                    waitingForNextClick = false;
                                    press_button_sound.play();
                                }
                            }
                            else if (event.type == sf::Event::MouseButtonReleased)
                            {
                                waitingForNextClick = true; // open flag when mouse released for accurate clicking check
                            }
                        }
                    }

                    if (current_player >= 3)
                    {
                        // for (int i = 0; i < 3; i++) {
                        //     cout << "P" << i + 1 << ":" << (activePlayers[i] ? "continue " : "fold ");
                        // }
                        // cout << "\n";

                        holdemStage = FLOP;
                        current_player = 0;
                    }

                    window.display();
                    continue;
                }

                else if (holdemStage == FLOP)
                {
                   
                    // Display bottom player cards (Player 1)
                    float bottomCardSpacing = 30.f;
                    float cardWidth = 125 * 0.25;    // 125 is the card image width
                    float cardHeight = 181.5 * 0.25; // 181.5 is the card image height

                    for (int i = 0; i < 2; i++)
                    {
                        string textFile = "cardpacks/" + playerHands[0][i].Rank + "_of_" + Suit_name[playerHands[0][i].suit_name] + ".png";
                        sf::Texture card_pick;
                        if (!card_pick.loadFromFile(textFile))
                        {
                            cout << "Failed to load file: " << textFile << endl;
                            continue;
                        }
                        sf::Sprite card_display(card_pick);
                        card_display.setScale(0.3, 0.3);

                        // Position at bottom center
                        float posX = 730 + (cardWidth + bottomCardSpacing) * i;
                        float posY = 740;
                        card_display.setPosition(posX, posY);

                        window.draw(card_display);

                        if (!activePlayers[0])
                        {
                            poker_back_card.setPosition(posX, posY);
                            window.draw(poker_back_card);
                        }
                    }

                    // Display left player cards (Player 2)
                    for (int i = 0; i < 2; i++)
                    {
                        string textFile = "cardpacks/" + playerHands[1][i].Rank + "_of_" + Suit_name[playerHands[1][i].suit_name] + ".png";
                        sf::Texture card_pick;
                        if (!card_pick.loadFromFile(textFile))
                        {
                            cout << "Failed to load file: " << textFile << endl;
                            continue;
                        }
                        sf::Sprite card_display(card_pick);
                        card_display.setScale(0.3, 0.3);

                        // Position at left center
                        float posX = 250;
                        float posY = 440 + (bottomCardSpacing + cardWidth) * i;
                        card_display.setPosition(posX, posY);
                        card_display.setRotation(90); // Rotate cards for left player
                        window.draw(card_display);

                        if (!activePlayers[1])
                        {
                            poker_back_card.setPosition(posX, posY);
                            poker_back_card.setRotation(90);
                            window.draw(poker_back_card);
                        }
                        poker_back_card.setRotation(0); // reset rotation
                    }

                    // Display right player cards (Player 3)
                    for (int i = 0; i < 2; i++)
                    {
                        string textFile = "cardpacks/" + playerHands[2][i].Rank + "_of_" + Suit_name[playerHands[2][i].suit_name] + ".png";
                        sf::Texture card_pick;
                        if (!card_pick.loadFromFile(textFile))
                        {
                            cout << "Failed to load file: " << textFile << endl;
                            continue;
                        }
                        sf::Sprite card_display(card_pick);
                        card_display.setScale(0.3, 0.3);

                        // Position at right center
                        float posX = 1360;
                        float posY = 590 + (cardHeight + bottomCardSpacing) * i;
                        card_display.setPosition(posX, posY);
                        card_display.setRotation(-90); // Rotate cards for right player
                        window.draw(card_display);

                        if (!activePlayers[2])
                        {
                            poker_back_card.setPosition(posX, posY);
                            poker_back_card.setRotation(-90);
                            window.draw(poker_back_card);
                        }
                        poker_back_card.setRotation(0); // reset rotation
                    }

                    // Display community cards in the middle
                    float communityCardSpacing = 30.f;
                    for (int i = 0; i < 5; i++)
                    {
                        string textFile = "cardpacks/" + communityCards[i].Rank + "_of_" + Suit_name[communityCards[i].suit_name] + ".png";
                        sf::Texture card_pick;
                        if (!card_pick.loadFromFile(textFile))
                        {
                            cout << "Failed to load file: " << textFile << endl;
                            continue;
                        }
                        sf::Sprite card_display(card_pick);
                        card_display.setScale(0.3, 0.3);

                        // Position in center of screen
                        float posX = 600 + (cardWidth + bottomCardSpacing) * i;
                        float posY = 300;
                        card_display.setPosition(posX, posY);

                        window.draw(card_display);
                        if (i > 2)
                        {
                            poker_back_card.setPosition(posX, posY);
                            window.draw(poker_back_card); // hiding card
                        }
                    }

                    // Draw player labels
                    sf::Text playerText;
                    playerText.setFont(font);
                    playerText.setCharacterSize(24);
                    playerText.setFillColor(sf::Color::Red);

                    // Bottom player
                    playerText.setString("Player 1");
                    playerText.setPosition(600, 750);
                    window.draw(playerText);

                    // Left player
                    playerText.setString("Player 2");
                    playerText.setPosition(20, 405);
                    window.draw(playerText);

                    // Right player
                    playerText.setString("Player 3");
                    playerText.setPosition(1500, 405);
                    window.draw(playerText);

                    window.draw(opt1);
                    window.draw(opt2);
                    window.draw(opt1_text);
                    window.draw(opt2_text);

                    if (current_player < 3)
                    {
                        // passing who has fold
                        while (current_player < 3 && !activePlayers[current_player])
                        {
                            // std::cout << "Bỏ qua Player " << current_player + 1 << " (đã fold)\n";
                            current_player++;
                        }

                        if (current_player < 3)
                        {
                            fold_or_not.setString("FLOP: Player " + to_string(current_player + 1) + ", do you want to fold?");
                            window.draw(fold_or_not);

                            if (event.type == sf::Event::MouseButtonPressed &&
                                event.mouseButton.button == sf::Mouse::Left &&
                                waitingForNextClick)
                            { // Chỉ xử lý khi đang đợi click mới

                                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                                sf::Vector2f mousePosFloat = window.mapPixelToCoords(mousePos);

                                std::cout << "Click " << mousePosFloat.x << ", " << mousePosFloat.y << "\n";

                                if (opt1.getGlobalBounds().contains(mousePosFloat))
                                {
                                    // std::cout << "Player " << current_player + 1 << " pick\n";
                                    activePlayers[current_player] = false;
                                    current_player++;
                                    waitingForNextClick = false; // clicking flag to avoid accident redundancy
                                    press_button_sound.play();
                                }
                                else if (opt2.getGlobalBounds().contains(mousePosFloat))
                                {
                                    // std::cout << "Player " << current_player + 1 << " pick\n";
                                    current_player++;
                                    waitingForNextClick = false;
                                    press_button_sound.play();
                                }
                            }
                            else if (event.type == sf::Event::MouseButtonReleased)
                            {
                                waitingForNextClick = true; // open flag when mouse released for accurate clicking check
                            }
                        }
                    }

                    if (current_player >= 3)
                    {
                        // for (int i = 0; i < 3; i++) {
                        //     cout << "P" << i + 1 << ":" << (activePlayers[i] ? "continue " : "fold ");
                        // }
                        // cout << "\n";

                        holdemStage = TURN;
                        current_player = 0;
                    }

                    window.display();
                    continue;
                }

                else if (holdemStage == TURN)
                {
                    // Display bottom player cards (Player 1)
                    float bottomCardSpacing = 30.f;
                    float cardWidth = 125 * 0.25;    // 125 is the card image width
                    float cardHeight = 181.5 * 0.25; // 181.5 is the card image height

                    for (int i = 0; i < 2; i++)
                    {
                        string textFile = "cardpacks/" + playerHands[0][i].Rank + "_of_" + Suit_name[playerHands[0][i].suit_name] + ".png";
                        sf::Texture card_pick;
                        if (!card_pick.loadFromFile(textFile))
                        {
                            cout << "Failed to load file: " << textFile << endl;
                            continue;
                        }
                        sf::Sprite card_display(card_pick);
                        card_display.setScale(0.3, 0.3);

                        // Position at bottom center
                        float posX = 730 + (cardWidth + bottomCardSpacing) * i;
                        float posY = 740;
                        card_display.setPosition(posX, posY);

                        window.draw(card_display);

                        if (!activePlayers[0])
                        {
                            poker_back_card.setPosition(posX, posY);
                            window.draw(poker_back_card);
                        }
                    }

                    // Display left player cards (Player 2)
                    for (int i = 0; i < 2; i++)
                    {
                        string textFile = "cardpacks/" + playerHands[1][i].Rank + "_of_" + Suit_name[playerHands[1][i].suit_name] + ".png";
                        sf::Texture card_pick;
                        if (!card_pick.loadFromFile(textFile))
                        {
                            cout << "Failed to load file: " << textFile << endl;
                            continue;
                        }
                        sf::Sprite card_display(card_pick);
                        card_display.setScale(0.3, 0.3);

                        // Position at left center
                        float posX = 250;
                        float posY = 440 + (bottomCardSpacing + cardWidth) * i;
                        card_display.setPosition(posX, posY);
                        card_display.setRotation(90); // Rotate cards for left player
                        window.draw(card_display);

                        if (!activePlayers[1])
                        {
                            poker_back_card.setPosition(posX, posY);
                            poker_back_card.setRotation(90);
                            window.draw(poker_back_card);
                        }
                        poker_back_card.setRotation(0); // reset rotation
                    }

                    // Display right player cards (Player 3)
                    for (int i = 0; i < 2; i++)
                    {
                        string textFile = "cardpacks/" + playerHands[2][i].Rank + "_of_" + Suit_name[playerHands[2][i].suit_name] + ".png";
                        sf::Texture card_pick;
                        if (!card_pick.loadFromFile(textFile))
                        {
                            cout << "Failed to load file: " << textFile << endl;
                            continue;
                        }
                        sf::Sprite card_display(card_pick);
                        card_display.setScale(0.3, 0.3);

                        // Position at right center
                        float posX = 1360;
                        float posY = 590 + (cardHeight + bottomCardSpacing) * i;
                        card_display.setPosition(posX, posY);
                        card_display.setRotation(-90); // Rotate cards for right player
                        window.draw(card_display);

                        if (!activePlayers[2])
                        {
                            poker_back_card.setPosition(posX, posY);
                            poker_back_card.setRotation(-90);
                            window.draw(poker_back_card);
                        }
                        poker_back_card.setRotation(0); // reset rotation
                    }

                    // Display community cards in the middle
                    float communityCardSpacing = 30.f;
                    for (int i = 0; i < 5; i++)
                    {
                        string textFile = "cardpacks/" + communityCards[i].Rank + "_of_" + Suit_name[communityCards[i].suit_name] + ".png";
                        sf::Texture card_pick;
                        if (!card_pick.loadFromFile(textFile))
                        {
                            cout << "Failed to load file: " << textFile << endl;
                            continue;
                        }
                        sf::Sprite card_display(card_pick);
                        card_display.setScale(0.3, 0.3);

                        // Position in center of screen
                        float posX = 600 + (cardWidth + bottomCardSpacing) * i;
                        float posY = 300;
                        card_display.setPosition(posX, posY);

                        window.draw(card_display);
                        if (i > 3)
                        {
                            poker_back_card.setPosition(posX, posY);
                            window.draw(poker_back_card); // hiding card
                        }
                    }

                    // Draw player labels
                    sf::Text playerText;
                    playerText.setFont(font);
                    playerText.setCharacterSize(24);
                    playerText.setFillColor(sf::Color::Red);

                    // Bottom player
                    playerText.setString("Player 1");
                    playerText.setPosition(600, 750);
                    window.draw(playerText);

                    // Left player
                    playerText.setString("Player 2");
                    playerText.setPosition(20, 405);
                    window.draw(playerText);

                    // Right player
                    playerText.setString("Player 3");
                    playerText.setPosition(1500, 405);
                    window.draw(playerText);

                    window.draw(opt1);
                    window.draw(opt2);
                    window.draw(opt1_text);
                    window.draw(opt2_text);

                    if (current_player < 3)
                    {
                        // passing who has fold
                        while (current_player < 3 && !activePlayers[current_player])
                        {
                            // std::cout << "Bỏ qua Player " << current_player + 1 << " (đã fold)\n";
                            current_player++;
                        }

                        if (current_player < 3)
                        {
                            fold_or_not.setString("TURN: Player " + to_string(current_player + 1) + ", do you want to fold?");
                            window.draw(fold_or_not);

                            if (event.type == sf::Event::MouseButtonPressed &&
                                event.mouseButton.button == sf::Mouse::Left &&
                                waitingForNextClick)
                            { // Chỉ xử lý khi đang đợi click mới

                                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                                sf::Vector2f mousePosFloat = window.mapPixelToCoords(mousePos);

                                std::cout << "Click " << mousePosFloat.x << ", " << mousePosFloat.y << "\n";

                                if (opt1.getGlobalBounds().contains(mousePosFloat))
                                {
                                    // std::cout << "Player " << current_player + 1 << " pick\n";
                                    activePlayers[current_player] = false;
                                    current_player++;
                                    waitingForNextClick = false; // clicking flag to avoid accident redundancy
                                    press_button_sound.play();
                                }
                                else if (opt2.getGlobalBounds().contains(mousePosFloat))
                                {
                                    // std::cout << "Player " << current_player + 1 << " pick\n";
                                    current_player++;
                                    waitingForNextClick = false;
                                    press_button_sound.play();
                                }
                            }
                            else if (event.type == sf::Event::MouseButtonReleased)
                            {
                                waitingForNextClick = true; // open flag when mouse released for accurate clicking check
                            }
                        }
                    }

                    if (current_player >= 3)
                    {
                        // for (int i = 0; i < 3; i++) {
                        //     cout << "P" << i + 1 << ":" << (activePlayers[i] ? "continue " : "fold ");
                        // }
                        // cout << "\n";

                        holdemStage = RIVER;
                        current_player = 0;
                    }

                    window.display();
                    continue;
                }

                else if (holdemStage == RIVER)
                {
                    // Display bottom player cards (Player 1)
                    float bottomCardSpacing = 30.f;
                    float cardWidth = 125 * 0.25;    // 125 is the card image width
                    float cardHeight = 181.5 * 0.25; // 181.5 is the card image height

                    for (int i = 0; i < 2; i++)
                    {
                        string textFile = "cardpacks/" + playerHands[0][i].Rank + "_of_" + Suit_name[playerHands[0][i].suit_name] + ".png";
                        sf::Texture card_pick;
                        if (!card_pick.loadFromFile(textFile))
                        {
                            cout << "Failed to load file: " << textFile << endl;
                            continue;
                        }
                        sf::Sprite card_display(card_pick);
                        card_display.setScale(0.3, 0.3);

                        // Position at bottom center
                        float posX = 730 + (cardWidth + bottomCardSpacing) * i;
                        float posY = 740;
                        card_display.setPosition(posX, posY);

                        window.draw(card_display);

                        if (!activePlayers[0])
                        {
                            poker_back_card.setPosition(posX, posY);
                            window.draw(poker_back_card);
                        }
                    }

                    // Display left player cards (Player 2)
                    for (int i = 0; i < 2; i++)
                    {
                        string textFile = "cardpacks/" + playerHands[1][i].Rank + "_of_" + Suit_name[playerHands[1][i].suit_name] + ".png";
                        sf::Texture card_pick;
                        if (!card_pick.loadFromFile(textFile))
                        {
                            cout << "Failed to load file: " << textFile << endl;
                            continue;
                        }
                        sf::Sprite card_display(card_pick);
                        card_display.setScale(0.3, 0.3);

                        // Position at left center
                        float posX = 250;
                        float posY = 440 + (bottomCardSpacing + cardWidth) * i;
                        card_display.setPosition(posX, posY);
                        card_display.setRotation(90); // Rotate cards for left player
                        window.draw(card_display);

                        if (!activePlayers[1])
                        {
                            poker_back_card.setPosition(posX, posY);
                            poker_back_card.setRotation(90);
                            window.draw(poker_back_card);
                        }
                        poker_back_card.setRotation(0); // reset rotation
                    }

                    // Display right player cards (Player 3)
                    for (int i = 0; i < 2; i++)
                    {
                        string textFile = "cardpacks/" + playerHands[2][i].Rank + "_of_" + Suit_name[playerHands[2][i].suit_name] + ".png";
                        sf::Texture card_pick;
                        if (!card_pick.loadFromFile(textFile))
                        {
                            cout << "Failed to load file: " << textFile << endl;
                            continue;
                        }
                        sf::Sprite card_display(card_pick);
                        card_display.setScale(0.3, 0.3);

                        // Position at right center
                        float posX = 1360;
                        float posY = 590 + (cardHeight + bottomCardSpacing) * i;
                        card_display.setPosition(posX, posY);
                        card_display.setRotation(-90); // Rotate cards for right player
                        window.draw(card_display);

                        if (!activePlayers[2])
                        {
                            poker_back_card.setPosition(posX, posY);
                            poker_back_card.setRotation(-90);
                            window.draw(poker_back_card);
                        }
                        poker_back_card.setRotation(0); // reset rotation
                    }

                    // Display community cards in the middle
                    float communityCardSpacing = 30.f;
                    for (int i = 0; i < 5; i++)
                    {
                        string textFile = "cardpacks/" + communityCards[i].Rank + "_of_" + Suit_name[communityCards[i].suit_name] + ".png";
                        sf::Texture card_pick;
                        if (!card_pick.loadFromFile(textFile))
                        {
                            cout << "Failed to load file: " << textFile << endl;
                            continue;
                        }
                        sf::Sprite card_display(card_pick);
                        card_display.setScale(0.3, 0.3);

                        // Position in center of screen
                        float posX = 600 + (cardWidth + bottomCardSpacing) * i;
                        float posY = 300;
                        card_display.setPosition(posX, posY);

                        window.draw(card_display);
                    }

                    // Draw player labels
                    sf::Text playerText;
                    playerText.setFont(font);
                    playerText.setCharacterSize(24);
                    playerText.setFillColor(sf::Color::Red);

                    // Bottom player
                    playerText.setString("Player 1");
                    playerText.setPosition(600, 750);
                    window.draw(playerText);

                    // Left player
                    playerText.setString("Player 2");
                    playerText.setPosition(20, 405);
                    window.draw(playerText);

                    // Right player
                    playerText.setString("Player 3");
                    playerText.setPosition(1500, 405);
                    window.draw(playerText);

                    window.draw(opt1);
                    window.draw(opt2);
                    window.draw(opt1_text);
                    window.draw(opt2_text);

                    if (current_player < 3)
                    {
                        // passing who has fold
                        while (current_player < 3 && !activePlayers[current_player])
                        {
                            // std::cout << "Bỏ qua Player " << current_player + 1 << " (đã fold)\n";
                            current_player++;
                        }

                        if (current_player < 3)
                        {
                            fold_or_not.setString("RIVER: Player " + to_string(current_player + 1) + ", do you want to fold?");
                            window.draw(fold_or_not);

                            if (event.type == sf::Event::MouseButtonPressed &&
                                event.mouseButton.button == sf::Mouse::Left &&
                                waitingForNextClick)
                            { // Chỉ xử lý khi đang đợi click mới

                                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                                sf::Vector2f mousePosFloat = window.mapPixelToCoords(mousePos);

                                std::cout << "Click " << mousePosFloat.x << ", " << mousePosFloat.y << "\n";

                                if (opt1.getGlobalBounds().contains(mousePosFloat))
                                {
                                    // std::cout << "Player " << current_player + 1 << " pick\n";
                                    activePlayers[current_player] = false;
                                    current_player++;
                                    waitingForNextClick = false; // clicking flag to avoid accident redundancy
                                    press_button_sound.play();
                                }
                                else if (opt2.getGlobalBounds().contains(mousePosFloat))
                                {
                                    // std::cout << "Player " << current_player + 1 << " pick\n";
                                    current_player++;
                                    waitingForNextClick = false;
                                    press_button_sound.play();
                                }
                            }
                            else if (event.type == sf::Event::MouseButtonReleased)
                            {
                                waitingForNextClick = true; // open flag when mouse released for accurate clicking check
                            }
                        }
                    }

                    if (current_player >= 3)
                    {
                        // for (int i = 0; i < 3; i++) {
                        //     cout << "P" << i + 1 << ":" << (activePlayers[i] ? "continue " : "fold ");
                        // }
                        // cout << "\n";

                        holdemStage = SHOWDOWN;
                        current_player = 0;
                    }

                    window.display();
                    continue;
                }
                else if (holdemStage == SHOWDOWN)
                {

                    sf::Text Holdem_res;
                    Holdem_res.setFont(font);
                    Holdem_res.setPosition(500, 385);
                    Holdem_res.setCharacterSize(46);
                    Holdem_res.setFillColor(sf::Color::Red);

                    string holdem_result = compareHands(playerHands, activePlayers);

                    Holdem_res.setString(holdem_result);
                    window.draw(Holdem_res);

                    window.draw(homeButton);
                    window.draw(homeButtonText);
                    window.draw(replayButton);
                    window.draw(replayButtonText);

                    window.display();

                    // Handle input events (similar to other modes)
                    bool waitingForInput = true;
                    while (waitingForInput)
                    {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        sf::Vector2f mousePosFloat = window.mapPixelToCoords(mousePos);
                        std::cout << "Mouse clicked at: " << mousePosFloat.x << ", " << mousePosFloat.y << std::endl;
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

                                    if (homeButton.getGlobalBounds().contains(mousePosFloat.x, mousePosFloat.y))
                                    {
                                        waitingForInput = false;
                                        isGameStarted = false;
                                        checkButton = false;
                                        gameplay = false;
                                        mode3_check = false;

                                        holdemStage = FOLDING;
                                        isAgain = true;
                                        activePlayers = { true, true, true };
                                        current_player = 0;
                                        playerHands.clear();

                                        /*game_mode_1.stop();*/
                                        game_mode_3.stop();
                                        press_button_sound.play();
                                        music_entry.play();
                                    }
                                    if (replayButton.getGlobalBounds().contains(mousePosFloat.x, mousePosFloat.y))
                                    {
                                        waitingForInput = false;
                                        isGameStarted = true;
                                        checkButton = false;
                                        gameplay = true;

                                        holdemStage = FOLDING;
                                        isAgain = true;
                                        activePlayers = { true, true, true };
                                        current_player = 0;
                                        playerHands.clear();

                                        /*game_mode_1.stop();*/
                                        press_button_sound.play();
                                        /*music_entry.play();*/
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (mode1_check)
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
                int winner_pos = winner_info.first.first;       // get the first winner
                int winner_pos_draw = winner_info.first.second; // get the draw winner, if it not draw, this must be -1;
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
                    else if ((i + 1) == winner_pos_draw) // winner_second != -1
                        /*
                        check ai bang ai luu pos vao pair vayj chinh laij get_winner cho ra pair<int, pair<int, int>> cai int dau luu strength.
                        cai pair sau luu 2 nguoi hoa nhau ma lon nhat, neu nhu second = -1 thi lay winner_pos = first thoi
                        */
                    {
                        wintype = true;
                    }
                    update_player_data(store_name[i], wintype, winner_strength);
                    update_player_win_rate(store_name[i], get_win_rate(store_name[i]));
                    update_player_win_game(store_name[i], get_win_game(store_name[i]));
                }

                delete[] players; //free memory

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
                    string textFile = "cardpacks/" + card_store[i].first + "_of_" + card_store[i].second + ".png";
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
                    result = "TIE!"; // check who draw with who
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

                window.draw(resultText);
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

                                    check_register = false; // return home page
                                    check_leaderboard = false;
                                    check_change_leaderboard = false;
                                    mode1_check = false;

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

                                    check_leaderboard = false;
                                    check_change_leaderboard = false;

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
            else if (mode2_check)
            {
                // Create and shuffle deck for mode 2
                vector<Card2> deck = createDeck2(); // create a deck again because it has been deleted some card when dealing
                shuffleDeck2(deck);
                vector<pair<string, string>> card_store{}; // store for displaying it in the screen

                // Deal cards and calculate scores
                vector<int> scores(number_player_2); // store score for each player
                int maxScore = -1;
                bool bacaoExists = false;

                for (int i = 0; i < number_player_2; i++)
                {
                    vector<Card2> hand = dealHand2(deck); // deal 3 card to a hand and after that delete it from the deck
                    for (const Card2& card : hand)
                    {
                        string rankNames[] = { "", "ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king" };
                        string suitNames[] = { "hearts", "diamonds", "clubs", "spades" };
                        card_store.push_back({ rankNames[card.rank], suitNames[card.suit] }); // card.rank is a int from a enumerator
                    }

                    int score = calculateScore2(hand);
                    scores[i] = score;

                    if (score == 100)
                    {
                        bacaoExists = true;
                    }
                    if (score > maxScore)
                    {
                        maxScore = score;
                    }
                }

                // Draw background
                window.draw(background);

                // Display cards
                float cardSpacing = 30.f;
                float rowSpacing = 200.f;
                int cardsPerRow = 3; // Mode 2 has 3 cards per player

                for (int i = 0; i < card_store.size(); i++)
                {
                    string textFile = "cardpacks/" + card_store[i].first + "_of_" + card_store[i].second + ".png";
                    sf::Texture card_pick;
                    if (!card_pick.loadFromFile(textFile))
                    {
                        cout << "Failed to load file: " << textFile << endl;
                        continue;
                    }
                    sf::Sprite card_display(card_pick);
                    card_display.setScale(0.25, 0.25);

                    int row = i / cardsPerRow;
                    int col = i % cardsPerRow;

                    float posX = 200 + (125 + cardSpacing) * col;
                    float posY = 100 + row * rowSpacing;

                    if (i / 3 >= 3)
                    {
                        posX += 800;
                        posY -= 600;
                    }

                    card_display.setPosition(posX, posY);

                    // Display player number for each row
                    if (i % 3 == 0)
                    {
                        sf::Text Number;
                        Number.setFont(font);
                        Number.setFillColor(sf::Color::Red);
                        if (i / 3 >= 3)
                        {
                            Number.setPosition(788, posY);
                        }
                        else
                        {
                            Number.setPosition(20, posY);
                        }
                        Number.setCharacterSize(24);
                        Number.setString("Player " + to_string(row + 1));
                        window.draw(Number);
                    }
                    window.draw(card_display);
                }

                // Determine winner and display result
                if (bacaoExists)
                {
                    result = "Player(s) with 'Three Royals' win!";
                }
                else if (maxScore != -1)
                {
                    result = "Player(s) with highest score " + to_string(maxScore) + " win!";
                }
                else
                {
                    result = "No winner, all players are 'Bust'.";
                }

                sf::Text resultText;
                resultText.setFont(font);
                resultText.setCharacterSize(30);
                resultText.setFillColor(sf::Color::Red);
                resultText.setString(result);
                resultText.setPosition(0.f, 0.f);

                window.draw(resultText);
                window.draw(homeButton);
                window.draw(homeButtonText);
                window.draw(replayButton);
                window.draw(replayButtonText);
                window.display();

                bool waitingForInput = true;
                while (waitingForInput)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePosFloat = window.mapPixelToCoords(mousePos);
                    std::cout << "Mouse clicked at: " << mousePosFloat.x << ", " << mousePosFloat.y << std::endl;
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

                                if (homeButton.getGlobalBounds().contains(mousePosFloat.x, mousePosFloat.y))
                                {
                                    waitingForInput = false;

                                    isGameStarted = false;
                                    checkButton = false;
                                    gameplay = false;
                                    isEnteringPlayers = false; // reset all flag to thbe beggining

                                    check_register = false;
                                    check_leaderboard = false;
                                    check_change_leaderboard = false;
                                    mode2_check = false;

                                    currentPlayer = 0;
                                    number_player_2 = 0;
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

                                    check_leaderboard = false;
                                    check_change_leaderboard = false;

                                    currentPlayer = 0;
                                    number_player_2 = 0;
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
        }

        // mode 2
        // mode 3
        // leaderboard

        window.display(); // display after modification
    }

    return 0;
}

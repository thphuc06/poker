#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace sf;

// Enum d? qu?n l� tr?ng th�i m�n h�nh
enum GameState {
    LOGIN,
    PLAYING
};

int main() {
    // T?o c?a s? SFML
    RenderWindow window(VideoMode(800, 800), "Game Poker");

    // Tr?ng th�i hi?n t?i (ban d?u l� m�n h�nh dang nh?p)
    GameState currentState = LOGIN;

    // T?i h�nh ?nh cho m�n h�nh choi game (c� th? thay d?i t�y theo tr� choi c?a b?n)
    Texture gameTexture;
    if (!gameTexture.loadFromFile("C:/HCMUS/th.jpg")) {
        cout << "Khong the tai hinh anh.\n";
        return -1;
    }
    Sprite gameBackground(gameTexture);

    // Bi?n d? luu d? li?u ngu?i d�ng nh?p
    string userInput = "";
    bool typing = true;

    // N�t "V�o game"
    RectangleShape button(Vector2f(200, 50));
    button.setFillColor(Color::Blue);
    button.setPosition(300, 400);

    // Text hi?n th? tr�n n�t
    Font font;
    if (!font.loadFromFile("C:/HCMUS/arial.ttf")) {
        cout << "Khong the tai font.\n";
        return -1;
    }
    Text buttonText("Vao game", font, 24);
    buttonText.setFillColor(Color::White);
    buttonText.setPosition(330, 410);

    // V�ng l?p ch�nh
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            // ��ng c?a s? n?u nh?n n�t close
            if (event.type == Event::Closed)
                window.close();

            if (currentState == LOGIN) {
                // X? l� nh?p li?u t? ngu?i d�ng
                if (typing) {
                    if (event.type == Event::TextEntered) {
                        if (event.text.unicode == '\r') {
                            typing = false;
                        } else if (event.text.unicode == 8) {
                            if (!userInput.empty()) {
                                userInput.erase(userInput.end()-1);
                            }
                        } else if (event.text.unicode < 128) {
                            userInput+=(char)(event.text.unicode);
                        }
                    }
                }

                // Ki?m tra n?u ngu?i d�ng nh?p v�o n�t "V�o game"
                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        // Chuy?n sang tr?ng th�i choi game
                        currentState = PLAYING;

                        // Luu t�n ngu?i choi v�o file
                        ifstream fil("userdata.txt");
                        
                        ofstream file("userdata.txt", ios::app);
                        string line;
                        
                        
                        bool checksame=false;
                        
                        if (file.is_open()) {
                        	while(getline(fil,line)){
                        		if(line==userInput){
                        			fil.close();
                        			checksame=true;
                        			cout<<"TRUNG TEN";
								}
							}
							if(!checksame){
	                            file << userInput << endl;
							}
							fil.close();
							file.close();
                        } else {
                            cout << "Khong the mo file de ghi.\n";
                        }
                    }
                }
            }
        }

        // X�a m�n h�nh
        window.clear(Color::White);

        if (currentState == LOGIN) {
            // M�n h�nh dang nh?p
            Text inputText("Nhap ten nguoi dung: " + userInput, font, 24);
            inputText.setFillColor(Color::Black);
            inputText.setPosition(150, 200);

            // V? c�c ph?n t? trong m�n h�nh dang nh?p
            window.draw(inputText);
            window.draw(button);
            window.draw(buttonText);

        } else if (currentState == PLAYING) {
            // M�n h�nh choi game
            window.draw(gameBackground);
            // ? d�y b?n c� th? ph�t tri?n tr� choi c?a m�nh
        }

        // C?p nh?t m�n h�nh
        window.display();
    }

    return 0;
}


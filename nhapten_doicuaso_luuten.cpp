#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace sf;

// Enum d? qu?n lý tr?ng thái màn hình
enum GameState {
    LOGIN,
    PLAYING
};

int main() {
    // T?o c?a s? SFML
    RenderWindow window(VideoMode(800, 800), "Game Poker");

    // Tr?ng thái hi?n t?i (ban d?u là màn hình dang nh?p)
    GameState currentState = LOGIN;

    // T?i hình ?nh cho màn hình choi game (có th? thay d?i tùy theo trò choi c?a b?n)
    Texture gameTexture;
    if (!gameTexture.loadFromFile("C:/HCMUS/th.jpg")) {
        cout << "Khong the tai hinh anh.\n";
        return -1;
    }
    Sprite gameBackground(gameTexture);

    // Bi?n d? luu d? li?u ngu?i dùng nh?p
    string userInput = "";
    bool typing = true;

    // Nút "Vào game"
    RectangleShape button(Vector2f(200, 50));
    button.setFillColor(Color::Blue);
    button.setPosition(300, 400);

    // Text hi?n th? trên nút
    Font font;
    if (!font.loadFromFile("C:/HCMUS/arial.ttf")) {
        cout << "Khong the tai font.\n";
        return -1;
    }
    Text buttonText("Vao game", font, 24);
    buttonText.setFillColor(Color::White);
    buttonText.setPosition(330, 410);

    // Vòng l?p chính
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            // Ðóng c?a s? n?u nh?n nút close
            if (event.type == Event::Closed)
                window.close();

            if (currentState == LOGIN) {
                // X? lý nh?p li?u t? ngu?i dùng
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

                // Ki?m tra n?u ngu?i dùng nh?p vào nút "Vào game"
                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        // Chuy?n sang tr?ng thái choi game
                        currentState = PLAYING;

                        // Luu tên ngu?i choi vào file
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

        // Xóa màn hình
        window.clear(Color::White);

        if (currentState == LOGIN) {
            // Màn hình dang nh?p
            Text inputText("Nhap ten nguoi dung: " + userInput, font, 24);
            inputText.setFillColor(Color::Black);
            inputText.setPosition(150, 200);

            // V? các ph?n t? trong màn hình dang nh?p
            window.draw(inputText);
            window.draw(button);
            window.draw(buttonText);

        } else if (currentState == PLAYING) {
            // Màn hình choi game
            window.draw(gameBackground);
            // ? dây b?n có th? phát tri?n trò choi c?a mình
        }

        // C?p nh?t màn hình
        window.display();
    }

    return 0;
}


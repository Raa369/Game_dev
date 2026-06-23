#include <iostream>
#include <SFML/Graphics.hpp>

class Player{
    private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::IntRect film;
    sf::Clock timerAnimasi;
    float frameheight =32.0f;
    float framewidth =32.0f;
    int totalframe =24;
    float durasiPERframe = 0.002f;
    float kecepatanX=0.0f;
    float kecepatanY=0.0f;
    float hitboxwidth= 32.0f;
    float hitboxheight=32.0f;


    public:
    Player(){
        if(!texture.loadFromFile("running.png")){}
        sprite.setTexture(texture);
        film = sf::IntRect(0,0,framewidth,frameheight);
        sprite.setTextureRect(film);
        sprite.setOrigin(framewidth/2,frameheight/2);
        sprite.setPosition(540, 360);
    }

    void arah(bool kanan){
        if (kanan==true){
            sprite.setScale(1.0f,1.0f);
        }
        else{sprite.setScale(-1.0f,1.0f);}
    }

    void updateAnimation(){
        if(timerAnimasi.getElapsedTime().asSeconds() >= durasiPERframe){
            film.left += framewidth;
            if(film.left >= framewidth*totalframe){
                film.left=0;
            }
            sprite.scale(4,4);
            sprite.setTextureRect(film);
            timerAnimasi.restart();
        }
    }

    void statisAnimation(){
        film.left =0;
        sprite.setTextureRect(film);
    }
            

    void draw(sf::RenderWindow& window){ 
        window.draw(sprite);}

    sf::FloatRect gethitbox(){
        sf::Vector2f pos =sprite.getPosition();
        return sf::FloatRect(pos.x-hitboxwidth/2, pos.y-hitboxheight/2,hitboxwidth,hitboxheight);
    }

    
    void movement( float kX, float kY, sf::FloatRect obstacle){
        sprite.move(kX,0.0f);

        sf::Vector2f pos=sprite.getPosition();
        if(pos.x < 64.0f){sprite.setPosition(64.0f,pos.y);}
        if(pos.x > 1016.0f){sprite.setPosition(1016.0f,pos.y);}

        if (gethitbox().intersects(obstacle)){
            sprite.move(-kX,0.0f);
        }


         sprite.move(0.0f,kY);

        pos=sprite.getPosition();
        if(pos.y < 64.0f){sprite.setPosition(pos.x,64.0f);}
        if(pos.y > 656.0f){sprite.setPosition(pos.x,656.0f);}

        if (gethitbox().intersects(obstacle)){
            sprite.move(0.0f,-kY);
        }
    }


    
};

class ground{
    private:
    sf::RectangleShape lantai;

    public:
    ground(){
        lantai.setPosition(0.0f,500.0f);
        lantai.setSize(sf::Vector2f(1080.0f,400.0f));
        lantai.setFillColor(sf::Color::Black);
    }

    sf::FloatRect getbound(){
        return lantai.getGlobalBounds();
    }

 void draw(sf::RenderWindow& window){ 
        window.draw(lantai);}
    
};

int main(){
    Player user;
    ground lantai;
    sf::RenderWindow window(sf::VideoMode(1080, 720),"Game sederhana");
    window.setFramerateLimit(60);

    

    while (window.isOpen()){
        sf::Event event;

        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
            window.close();
        }
        bool gerak_gak =false;
        float kX;
        float kY;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)||sf::Keyboard::isKeyPressed(sf::Keyboard::A)){user.arah(false); kX=-15.0f; user.movement(kX,kY, lantai.getbound()); gerak_gak=true;}
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)||sf::Keyboard::isKeyPressed(sf::Keyboard::D)){user.arah(true); kX=15.0f; user.movement(kX,kY, lantai.getbound()); gerak_gak=true;}
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)||sf::Keyboard::isKeyPressed(sf::Keyboard::S)){user.arah(true); kY=15.0f; user.movement(kX,kY, lantai.getbound()); gerak_gak=true;}
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||sf::Keyboard::isKeyPressed(sf::Keyboard::W)){user.arah(true); kY=-15.0f; user.movement(kX,kY, lantai.getbound()); gerak_gak=true;}


        if(gerak_gak){user.updateAnimation();}
        else{user.statisAnimation();}


        window.clear(sf::Color(150,150,150));
        lantai.draw(window);
        user.draw(window);
        window.display();
    }
    return 0;
}

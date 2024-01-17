#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <utility>
const int offsetX = 50, offsetY = 85;
class ChessPiece{
    public:
        sf::Texture loader;
        sf::Sprite obrazek;
        char typ, barva;
        bool pohl;
        ChessPiece(std::string nazev){
            loader.loadFromFile(nazev);
            obrazek.setTexture(loader);
            barva = nazev[0];
            typ = nazev[1];
            pohl = false;
        }
};

ChessPiece* Sach[8][8];
void SachovCreate(std::vector<sf::VertexArray>& Sachov){
    Sachov.resize(64, sf::VertexArray(sf::Quads, 4));
    for(int i = 0; i < 64; i++){
        int x = (i % 8) * 100, y = i / 8 * 100; 
        Sachov[i][0].position = sf::Vector2f(x, y);
        Sachov[i][1].position = sf::Vector2f(x, y + 100);
        Sachov[i][2].position = sf::Vector2f(x + 100, y + 100);
        Sachov[i][3].position = sf::Vector2f(x + 100, y);
        if((i % 2 && !(i / 8 % 2)) || (!(i % 2) && i/ 8 % 2)){
            Sachov[i][0].color = sf::Color(176, 140, 100);
            Sachov[i][1].color = sf::Color(176, 140, 100);
            Sachov[i][2].color = sf::Color(176, 140, 100);
            Sachov[i][3].color = sf::Color(176, 140, 100);
        }
        else{
            Sachov[i][0].color = sf::Color(240, 220, 180);
            Sachov[i][1].color = sf::Color(240, 220, 180);
            Sachov[i][2].color = sf::Color(240, 220, 180);
            Sachov[i][3].color = sf::Color(240, 220, 180);

        }
    }
}
void Premistit(ChessPiece* jaky, int x, int y){
    Sach[x][y] = jaky;
    jaky->obrazek.setPosition(x*100 , y*100);
}
std::pair<int, int> Zjistit(sf::RenderWindow& window){
    sf::Vector2i pos1 = window.getPosition();
    sf::Vector2i pos2 = sf::Mouse::getPosition();
    int x = pos2.x - pos1.x - offsetX; int y =  pos2.y - pos1.y - offsetY;
    x += 50; y += 50;
    if(x < 0 || y < 0){
        x = -100;
    }
    return {x, y}; 
}
void vyber(sf::RenderWindow& window, ChessPiece** koho){
    std::vector<sf::VertexArray> ted;
    ted.resize(4, sf::VertexArray(sf::Quads, 4));
    for(int i = 0; i < 4; i++){
        ted[i][0].position = sf::Vector2f(200 + i * 100, 350);
        ted[i][1].position = sf::Vector2f(200 + i * 100, 350 + 100);
        ted[i][2].position = sf::Vector2f(200 + i * 100 + 100, 350 + 100);
        ted[i][3].position = sf::Vector2f(200 + i * 100 + 100, 350);
       
        ted[i][0].color = sf::Color::Green;
        ted[i][1].color = sf::Color::Green;
        ted[i][2].color = sf::Color::Green;
        ted[i][3].color = sf::Color::Green;    
        window.draw(ted[i]);
        
    }

    
    std::string barvos = "";
    barvos = (*koho)->barva;
    ChessPiece* q, *r, *b, *n;
    q = new ChessPiece(barvos + "q.png");r = new ChessPiece(barvos + "r.png");b = new ChessPiece(barvos + "b.png");n = new ChessPiece(barvos + "n.png") ;
    q->obrazek.setPosition(200, 350); r->obrazek.setPosition(300, 350); b->obrazek.setPosition(400, 350); n->obrazek.setPosition(500, 350);
    window.draw(q->obrazek); window.draw(r->obrazek); window.draw(b->obrazek); window.draw(n->obrazek);
    window.display();

    sf::Event event;
    while(true){
        while (window.pollEvent(event)){
            if(event.type == sf::Event::MouseButtonPressed){
                std::pair<int, int> par = Zjistit(window);
                if(par.second < 350 || par.second > 450) continue;
                if(par.first >= 200 && par.first <= 300){
                    *koho = new ChessPiece(barvos + "q.png");
                    return;
                }
                else if(par.first >= 300 && par.first <= 400){
                    *koho = new ChessPiece(barvos + "r.png"); 
                    return;
                }
                else if(par.first >= 400 && par.first <= 500){
                    *koho = new ChessPiece(barvos + "b.png"); 
                    return;
                }
                else if(par.first >= 500 && par.first <= 600){
                    *koho = new ChessPiece(barvos + "n.png"); 
                    return;
                }
            }
        }
    }

}

void NaCerveno(sf::RenderWindow& window, sf::VertexArray& redka);
void SachovDraw(std::vector<sf::VertexArray>& Sachov,sf::RenderWindow& window, bool prebarvit, std::vector<sf::VertexArray>& kdeZel, sf::VertexArray& redka){
    for(int i = 0; i < 64; i++){
        window.draw(Sachov[i]);
    }
    NaCerveno(window, redka);
    if(prebarvit){
        window.draw(kdeZel[0]);
        window.draw(kdeZel[1]);
    }
    for(int i = 0; i < 8; i++){
        for(int k = 0; k < 8; k++){
            if(Sach[i][k] != nullptr){
                window.draw(Sach[i][k]->obrazek);
            }
        }
    }
}
void PostavCreate(){
    for(int i = 0; i < 8; i++){
        Premistit(new ChessPiece("bp.png"), i, 1);
        Premistit(new ChessPiece("wp.png"), i, 6);
    }
    std::pair<int,std::string > druhyL[] = {{0, "r"}, {7,"r"}, {1, "n"}, {6, "n"}, {2, "b"}, {5, "b"}, {4, "k"}, {3, "q"}};
    for(auto& it2 : druhyL){
        Premistit(new ChessPiece("b" + it2.second + ".png"), it2.first, 0);
        Premistit(new ChessPiece("w" + it2.second + ".png"), it2.first, 7);
    }
}
bool JePrazdny(int x, int y){
    if(Sach[x][y] != nullptr) return false;
    return true;
}
bool rovne(int a, int odkud, int kam,int pos){
    for(int i = odkud - 1; i > kam; i--){
        if(pos == 0){
            if(!JePrazdny(i, a)) return false;
        }
        else{
            if(!JePrazdny(a, i)) return false;
        }
        
    }
    for(int i = odkud + 1; i < kam; i++){
        if(pos == 0){
            if(!JePrazdny(i, a)) return false;
        }
        else{
            if(!JePrazdny(a, i)) return false;
        }
        
    }
    return true;
}
bool krizne(int x1, int y1, int x2, int y2){
    if(x2 > x1 && y2 > y1){
        for(int i = 1; i < y2 - y1; i++){
            if(!JePrazdny(x1 + i, y1 + i)) return false;
        }
    } 
    else if(x2 > x1 && y2 < y1){
        for(int i = 1; i < x2 - x1; i++){
            if(!JePrazdny(x1 + i, y1 - i)) return false;
        }
    }
    else if(x2 < x1 && y2 < y1){
        for(int i = 1; i < x1 - x2; i++){
            if(!JePrazdny(x1 - i, y1 - i)) return false;
        }
    }
    else {
        for(int i = 1; i < x1 - x2; i++){
            if(!JePrazdny(x1 - i, y1 + i)) return false;
        }
    }        
    return true;
    
}
bool poprve = true, spec = false, Ksach = false;
std::pair<int, int> kdo;
bool nebezpeci(std::pair<int,int> kde, char barvos, bool kralos);
std::pair<bool, int> enpes;
bool rosada = false;
bool muze(std::pair<int, int> par, std::pair<int, int>& par2 ){
    ChessPiece odkud = *Sach[par.first][par.second];
    bool fg = false;
    if(par2.first > 7 || par2.first < 0 || par2.second > 7 || par2.second < 0) return false;
    if(Sach[par2.first][par2.second] != nullptr){
        fg = true;
        ChessPiece kam = *Sach[par2.first][par2.second];
        if(odkud.barva == kam.barva){
            return false;
        }
    }
    if(odkud.typ == 'p'){
        if(fg){
            if(odkud.barva == 'w' && par.second - 1 == par2.second && (par2.first - 1 == par.first || par2.first + 1 == par.first)){
                if(par2.second == 0 || par2.second == 7){

                }
                return true;
            }
            else if(odkud.barva == 'b' && par.second + 1 == par2.second && (par2.first -1 == par.first || par2.first + 1 == par.first)){
                return true;
            }
            else{
                return false;
            }
        }
        if(enpes.second != -1){
            if(odkud.barva == 'w' && !enpes.first && par.second - 1 == par2.second && (par2.first - 1 == par.first || par2.first + 1 == par.first) && par2.first == enpes.second && par2.second == 2){
                spec = true;
                return true;
            }
            else if(odkud.barva == 'b' && enpes.first && par.second + 1 == par2.second && (par2.first - 1 == par.first || par2.first + 1 == par.first) && par2.first == enpes.second && par2.second == 5){
                spec = true;
                return true;
            }
        }
        if(odkud.barva == 'w' && par.first == par2.first && (par.second - 2 == par2.second && par.second == 6 && JePrazdny(par.first,par.second-1))){
            enpes.first = true;
            enpes.second = par.first;
        }

        else if(odkud.barva == 'b' && par.first == par2.first && (par.second + 2 == par2.second && par.second == 1 && JePrazdny(par.first, par.second +1))){
            enpes.first = false;
            enpes.second = par.first;
        }
        if(odkud.barva == 'w' && par.first == par2.first && (par.second - 1 == par2.second || (par.second - 2 == par2.second && par.second == 6 && JePrazdny(par.first,par.second-1)))) return true;
        else if(odkud.barva == 'b' && par.first == par2.first && (par.second + 1 == par2.second || (par.second + 2 == par2.second && par.second == 1 && JePrazdny(par.first, par.second +1)))) return true;
        else return false;
    }
    else if(odkud.typ == 'n'){
        if((par.first - 1 == par2.first && par.second - 2 == par2.second) || (par.first + 1 == par2.first && par.second - 2 == par2.second)) return true;
        else if((par.first - 1 == par2.first && par.second + 2 == par2.second) || (par.first + 1 == par2.first && par.second + 2 == par2.second)) return true;
        else if((par.first - 2 == par2.first && par.second + 1 == par2.second) || (par.first - 2 == par2.first && par.second - 1 == par2.second)) return true;
        else if((par.first + 2 == par2.first && par.second + 1 == par2.second) || (par.first + 2 == par2.first && par.second - 1 == par2.second)) return true;
        else return false;
                
    }
    else if(odkud.typ == 'r'){
        if(par.first == par2.first){
            return rovne(par.first, par.second, par2.second, 1);
        }
        else if(par.second == par2.second){
            return rovne(par.second, par.first, par2.first, 0); 
        }
        else{
            return false;
        }
    }
    else if(odkud.typ == 'q'){
        if(abs(par2.first - par.first) == abs(par2.second - par.second)){
            return krizne(par.first, par.second, par2.first, par2.second);
        }
        else if(par.first == par2.first){
            return rovne(par.first, par.second, par2.second, 1);
        }
        else if(par.second == par2.second){
            return rovne(par.second, par.first, par2.first, 0); 
        }
        else{
            return false;
        }
    }
    else if(odkud.typ == 'b'){
        if(abs(par2.first - par.first) == abs(par2.second - par.second)){
            return krizne(par.first, par.second, par2.first, par2.second);
        }
        else{
            return false;
        }
    }
    else{
        if(!odkud.pohl && par2.first == 2 && Sach[0][par2.second] != nullptr && Sach[0][par2.second]->barva == odkud.barva && Sach[0][par2.second]->typ == 'r' && Sach[0][par2.second]->pohl == false  && Sach[1][par2.second] == nullptr && Sach[2][par2.second] == nullptr && Sach[3][par2.second] == nullptr){
            if(!nebezpeci({2, par2.second}, odkud.barva, false) && !nebezpeci({3, par2.second}, odkud.barva, false) && !nebezpeci({4, par2.second}, odkud.barva, false)){
                Premistit(Sach[0][par2.second], 3, par2.second);
                Sach[0][par2.second] = nullptr;
                rosada = true;
                return true;

            }
        }
        else if(!odkud.pohl && par2.first == 6 && Sach[7][par2.second] != nullptr && Sach[7][par2.second]->barva == odkud.barva &&Sach[7][par2.second]->typ == 'r' && Sach[7][par2.second]->pohl == false && Sach[5][par2.second] == nullptr && Sach[6][par2.second] == nullptr){
            if(!nebezpeci({4, par2.second}, odkud.barva, false) && !nebezpeci({5, par2.second}, odkud.barva, false) && !nebezpeci({6, par2.second}, odkud.barva, false)){
                Premistit(Sach[7][par2.second], 5, par2.second);
                Sach[7][par2.second] = nullptr;
                rosada = true;
                return true;
            }
        }
        else if(abs(par2.first - par.first) > 1 || abs(par2.second - par.second) > 1) return false;
    }
    return true;
}

bool vnebezpeci(std::pair<int,int> kde, char barvos, std::pair<int, int> co){
    bool flag = true;
    ChessPiece* tmp = Sach[kde.first][kde.second];
    for(int i = 0; i < 8; i++){
        for(int k = 0; k < 8; k++){
            if(Sach[i][k] != nullptr && Sach[i][k]->barva == barvos && Sach[i][k]->typ != 'k'){
                if(muze({i, k}, kde)){
                    Sach[kde.first][kde.second] = Sach[i][k];
                    Sach[i][k] = nullptr;
                    flag = nebezpeci(co, Sach[kde.first][kde.second]->barva, false);
                    Sach[i][k] = Sach[kde.first][kde.second];
                    Sach[kde.first][kde.second] = tmp;
                    if(!flag){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
bool safety(int x, int y){
    std::vector<std::pair<int,int>> moz = {{x, y + 1}, {x,y - 1}, {x+ 1, y+1}, {x+ 1, y},{x+ 1, y - 1}, {x - 1, y +1}, {x-1, y},{x - 1, y- 1}};
    for(int i = 0; i < 8; i++){
        if(moz[i].first <= 7 && moz[i].first >= 0 && moz[i].second <= 7 && moz[i].second >= 0){
            ChessPiece* temp = Sach[moz[i].first][moz[i].second];
            if(Sach[moz[i].first][moz[i].second] != nullptr && Sach[x][y]->barva != Sach[moz[i].first][moz[i].second]->barva){
                Sach[moz[i].first][moz[i].second] = nullptr;
            }
            if(!nebezpeci(moz[i], Sach[x][y]->barva, false) && (Sach[moz[i].first][moz[i].second] == nullptr || Sach[moz[i].first][moz[i].second]->barva != Sach[x][y]->barva)){
                Sach[moz[i].first][moz[i].second] = temp; 
                return true;
            }
            Sach[moz[i].first][moz[i].second] = temp; 
        }
    }
    for(int i = 0; i < 8; i++){
        for(int k = 0; k < 8; k++){
            if((Sach[i][k] == nullptr || Sach[i][k]->barva != Sach[x][y]->barva) && !vnebezpeci({i,k}, Sach[x][y]->barva, {x,y})){
                return true; 
            }
        }
    }
    return false;
}
bool nebezpeci(std::pair<int,int> kde, char barvos, bool kralos){
    for(int i = 0; i < 8; i++){
        for(int k = 0; k < 8; k++){
            if(Sach[i][k] != nullptr && Sach[i][k]->barva != barvos){
                if(Sach[i][k]->typ == 'k' && kralos) continue;
                if(muze({i,k}, kde)){
                    kdo.first = i; kdo.second = k;
                    return true;
                }
            }
        }
    }
    return false;
}
bool jeKneb(char barvos){
    for(int i = 0; i < 8; i++){
        for(int k = 0; k < 8; k++){
            if(Sach[i][k] != nullptr && Sach[i][k]->typ == 'k' && Sach[i][k]->barva == barvos && nebezpeci({i,k}, barvos, false)) return true;
        }
    }
    return false;
}
bool jeKsachmat(){
    for(int i = 0; i < 8; i++){
        for(int k = 0; k < 8; k++){
            if(Sach[i][k] != nullptr && Sach[i][k]->typ == 'k'){
                if(nebezpeci({i, k}, Sach[i][k]->barva , false)){
                    Ksach = true;
                    if(!safety(i, k)){
                        return true;
                    }
                }
            }
        }
    }
    return false;

}
bool VKlidu(ChessPiece* koho, std::pair<int, int> par, std::pair<int, int> par2){
    if(!muze(par, par2)) return false;
    ChessPiece* temp[8][8];
    for(int i = 0; i < 8; i++){
        for(int k = 0; k < 8; k++){
            temp[i][k] = Sach[i][k];
        }
    }
    Sach[par.first][par.second] = nullptr;
    
    if(spec){
        if(enpes.first){
            Sach[par2.first][par2.second -1] = nullptr;
        }
        else{
            Sach[par2.first][par2.second + 1] = nullptr;
        }

    }

    Premistit(koho, par2.first, par2.second);
    bool fgram = jeKneb(koho->barva);
    for(int i = 0; i < 8; i++){
        for(int k = 0; k < 8; k++){
            Sach[i][k] = temp[i][k];
        }
    }
    Premistit(koho, par.first, par.second);
    return !fgram;
}
void NaCerveno(sf::RenderWindow& window, sf::VertexArray& redka){
    for(int i = 0; i < 8; i++){
        for(int k = 0; k < 8; k++){
            if(Sach[i][k] != nullptr && Sach[i][k]->typ == 'k' && nebezpeci({i, k}, Sach[i][k]->barva, false)){
                redka[0].position = sf::Vector2f(i * 100, k * 100);
                redka[1].position = sf::Vector2f((i + 1) * 100, k * 100);
                redka[2].position = sf::Vector2f((i+1) * 100, (k+1) * 100);
                redka[3].position = sf::Vector2f(i * 100, (k+1) * 100);
                
                redka[0].color = sf::Color::Red;
                redka[1].color = sf::Color::Red;
                redka[2].color = sf::Color::Red;
                redka[3].color = sf::Color::Red;

                window.draw(redka);
            }
        }
    }
}
bool Pat(char barvos){
    for(int i = 0; i < 8; i++){
        for(int k = 0;k < 8; k++){
            if(Sach[i][k] != nullptr && Sach[i][k]->barva == barvos){
                for(int j = 0; j < 8; j++){
                    for(int l = 0; l < 8; l++){
                        if(VKlidu(Sach[i][k], {i, k}, {j, l})) return false;
                    }
                }
            }
        }
    }
    return true;
}
int main()
{
    std::pair<int, int> par; 
    sf::Text text;
    sf::Font font;
    bool drzi = false;
    bool prebarvit = false;
    std::vector<sf::VertexArray> kdeZel;
    sf::VertexArray redka(sf::Quads, 4);
    kdeZel.resize(2, sf::VertexArray(sf::Quads, 4));
    for(int i = 0; i < 2; i++){
        for(int k = 0; k < 4; k++){
            kdeZel[i][k].color = sf::Color(0, 255, 0);
        }
    }
    ChessPiece* koho = nullptr;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess");
    std::vector<sf::VertexArray> Sachov;   
    int tah = 0;
    bool stop = false;
    SachovCreate(Sachov);
    PostavCreate();
    while (window.isOpen())
    {
        sf::Event event;
        if(stop){
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            continue;
        }
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::MouseButtonPressed){
                par = Zjistit(window);
                par.first /= 100; par.second /= 100;
                if(Sach[par.first][par.second] != nullptr){
                    if((tah % 2 == 0 && Sach[par.first][par.second]->barva == 'w') || (tah % 2 == 1 && Sach[par.first][par.second]->barva == 'b')){
                        drzi = true;
                        koho = Sach[par.first][par.second];
                    }
                }
            }
            if(drzi){
                sf::Vector2i pos1 = window.getPosition();
                sf::Vector2i pos2 = sf::Mouse::getPosition();
                koho->obrazek.setPosition(pos2.x - pos1.x - offsetX, pos2.y - pos1.y - offsetY);
            }
            if(event.type == sf::Event::MouseButtonReleased){
                if(drzi == false) continue;
                std::pair<int, int> par2 = Zjistit(window);
                par2.first /= 100; par2.second /= 100;
                if(enpes.second != -1 && !poprve){
                    enpes.second = -1;
                    poprve = true;
                } 
                else if(enpes.second != -1){
                    poprve = false;
                }
                if(muze(par, par2)){ 
                    if(VKlidu(koho, par, par2) || rosada == true){
                        Sach[par.first][par.second] = nullptr;
                        
                        if(spec){
                            if(enpes.first){
                                Sach[par2.first][par2.second -1] = nullptr;
                            }
                            else{
                                Sach[par2.first][par2.second + 1] = nullptr;
                            }
                            spec = false;
                        }

                        Premistit(koho, par2.first, par2.second);
                        tah++;
                        if(koho->typ == 'p' && (par2.second == 0 || par2.second == 7)) vyber(window, &koho);
                        Premistit(koho, par2.first, par2.second);

                        int x =  par.first * 100, y = par.second * 100; 
                        kdeZel[0][0].position = sf::Vector2f(x, y);
                        kdeZel[0][1].position = sf::Vector2f(x, y + 100);
                        kdeZel[0][2].position = sf::Vector2f(x + 100, y + 100);
                        kdeZel[0][3].position = sf::Vector2f(x + 100, y);
                        x = par2.first * 100; y = par2.second * 100; 
                        kdeZel[1][0].position = sf::Vector2f(x, y);
                        kdeZel[1][1].position = sf::Vector2f(x, y + 100);
                        kdeZel[1][2].position = sf::Vector2f(x + 100, y + 100);
                        kdeZel[1][3].position = sf::Vector2f(x + 100, y);
                        prebarvit = true;
                        koho->pohl = true;
                        if(jeKsachmat()) {
                            stop = true;
                            font.loadFromFile("BigBlueTerm437NerdFont-Regular.ttf");
                            text.setFont(font);
                            if(tah % 2){

                                text.setString("White won!");
                            }
                            else{
                                text.setString("Black won!");
                            }
                            text.setCharacterSize(50);
                            text.setFillColor(sf::Color::Blue);
                            text.setPosition(240, 360);
                            window.draw(text);
                        }
                        else if((tah % 2 && Pat('b')) || (tah % 2 == 0 && Pat('w'))){
                            stop = true;
                            font.loadFromFile("BigBlueTerm437NerdFont-Regular.ttf");
                            text.setFont(font);
                            text.setString("Pat!");
                            text.setCharacterSize(50);
                            text.setFillColor(sf::Color::Blue);
                            text.setPosition(270, 360);
                            window.draw(text);
                        }
                        rosada = false;
                    }
                }
                else{
                    Premistit(koho, par.first, par.second);
                }
                drzi = false;
                koho = nullptr;
            }
        }
        window.clear();
        SachovDraw(Sachov, window, prebarvit, kdeZel, redka); 
        if (koho != nullptr) {window.draw(koho->obrazek);}
        //vyber(window);
        if(stop) {
            window.draw(text);
        }
        window.display();
    }


    return 0;
}

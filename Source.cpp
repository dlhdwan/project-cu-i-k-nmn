#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
using namespace std;
// Kích thước cửa sổ
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 565;

// Đường dẫn đến tệp hình ảnh nền
const char* BACKGROUND_IMAGE_PATH = "bg.JPG";
// Đường dẫn nhân vật 1
const char* CHARACTER_1_IMAGE_PATH = "Player_1//player_1_dung.png";
// Đường dẫn nhân vật 2
const char* CHARACTER_2_IMAGE_PATH = "Player_2//player_2_dung_1.png";

//ảnh nv 1 khi  qua trái 
const char* CHARACTER_1_left = "Player_1//player_1_dung_2.png";
// ảnh nv2 khi qua phải
const char* CHARACTER_2_right = "Player_2//player_2_dung.png";

// Hàm khởi tạo cửa sổ SDL
SDL_Window* initSDLWindow() {
    SDL_Window* window = SDL_CreateWindow("Background Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        exit(1);
    }
    return window;
}

// Hàm khởi tạo renderer SDL
SDL_Renderer* initSDLRenderer(SDL_Window* window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        exit(1);
    }
    return renderer;
}

// Hàm load texture từ hình ảnh
SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* imagePath) {
    SDL_Surface* surface = IMG_Load(imagePath);

    if (surface == NULL) {
        std::cerr << "Unable to load image! SDL_image Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (texture == NULL) {
        std::cerr << "Unable to create texture from image! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
    return texture;
}
// Hàm khởi tạo Rect của nhân vật
SDL_Rect initCharacterRect(SDL_Surface* characterSurface, int x, int y, int width, int height) {
    SDL_Rect characterRect = { x, y, width, height };
    return characterRect;
}

// Hàm xử lý sự kiện SDL
void handleEvents(SDL_Rect& characterRect1, SDL_Rect& characterRect2, SDL_Rect& nv1_left, SDL_Rect& nv2_rigth, int characterSpeed1, int characterSpeed2) {
    SDL_Event e;
    
    // status lưu trạng thái 2 nhân vật
    int status1 = 0; // nhân vật 1
    int status2 = 0; // nhân vật 2
    
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }
        else if (e.type == SDL_KEYDOWN) {
            const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
            // Tính toán tốc độ di chuyển của nhân vật 1
            int currentCharacterSpeed1 = 0;
            if (currentKeyStates[SDL_SCANCODE_D]) {
                currentCharacterSpeed1 += characterSpeed1;
                status1 = 1;
            }
            if (currentKeyStates[SDL_SCANCODE_A]) {
                currentCharacterSpeed1 -= characterSpeed1;
                status1 = -1;
            }

            // Tính toán tốc độ di chuyển của nhân vật 2
            int currentCharacterSpeed2 = 0;
            if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
                currentCharacterSpeed2 += characterSpeed2;
                status2 = -1;
            }
            if (currentKeyStates[SDL_SCANCODE_LEFT]) {
                currentCharacterSpeed2 -= characterSpeed2;
                status2 = 1;
            }
            // Cập nhật vị trí của từng nhân vật dựa trên tốc độ tính toán
            characterRect1.x += currentCharacterSpeed1;
            characterRect2.x += currentCharacterSpeed2;
        }
        // Kiểm tra giá trị của status1
        /*if(status1 == -1) // Nhân vật 1 đang chạy sang trái
        {
            SDL_RenderCopy(renderer, nv1_left, NULL, &characterRect1); // Dùng hình ảnh nv1_left
        }

        // Kiểm tra giá trị của status2
        if (status2 == -1) // Nhân vật 2 đang chạy sang phải
        {
            SDL_RenderCopy(renderer, nv2_rigth , NULL, &characterRect2); // Dùng hình ảnh nv2_right
        }*/

    }

    // Giới hạn vị trí của nhân vật 1 trong khung hình
    if (characterRect1.x < 0) {
        characterRect1.x = 0;
    }
    else if (characterRect1.x > SCREEN_WIDTH - characterRect1.w) {
        characterRect1.x = SCREEN_WIDTH - characterRect1.w;
    }

    // Giới hạn vị trí của nhân vật 2 trong khung hình
    if (characterRect2.x < 0) {
        characterRect2.x = 0;
    }
    else if (characterRect2.x > SCREEN_WIDTH - characterRect2.w) {
        characterRect2.x = SCREEN_WIDTH - characterRect2.w;
    }
}



int main(int argc, char* args[]) {
    // Khởi tạo SDL và kiểm tra lỗi
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Khởi tạo SDL_image và kiểm tra lỗi
    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = initSDLWindow();
    SDL_Renderer* renderer = initSDLRenderer(window);
    SDL_Texture* backgroundTexture = loadTexture(renderer, BACKGROUND_IMAGE_PATH);
    SDL_Texture* characterTexture1 = loadTexture(renderer, CHARACTER_1_IMAGE_PATH);
    SDL_Texture* characterTexture2 = loadTexture(renderer, CHARACTER_2_IMAGE_PATH);
    SDL_Texture* character1_left = loadTexture(renderer, CHARACTER_1_left);
    SDL_Texture* character2_right = loadTexture(renderer, CHARACTER_2_right);


    SDL_Rect characterRect1 = initCharacterRect(IMG_Load(CHARACTER_1_IMAGE_PATH), 100, 300, 165, 250);
    SDL_Rect characterRect2 = initCharacterRect(IMG_Load(CHARACTER_2_IMAGE_PATH), SCREEN_WIDTH - 100 - characterRect1.w, 300, characterRect1.w, characterRect1.h);
    SDL_Rect nv1_left = initCharacterRect(IMG_Load(CHARACTER_1_left), 100, 300, 165, 250);
    SDL_Rect nv2_right = initCharacterRect(IMG_Load(CHARACTER_2_right),characterRect1.w, 300, characterRect1.w, characterRect1.h);

    const int characterSpeed1 = 10;
    const int characterSpeed2 = 10;

    // Chờ người dùng đóng cửa sổ
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        handleEvents(characterRect1, characterRect2, nv1_left, nv2_right, characterSpeed1, characterSpeed2);

        // Clear và vẽ background lên renderer
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        // Vẽ nhân vật lên renderer
        SDL_RenderCopy(renderer, characterTexture1, NULL, &characterRect1);
        SDL_RenderCopy(renderer, characterTexture2, NULL, &characterRect2);
        
        //SDL_RenderCopy(renderer, character1_left, NULL, &nv1_left);
        //SDL_RenderCopy(renderer, character2_right, NULL, &nv2_right);
        // Hiển thị renderer
        SDL_RenderPresent(renderer);
    }

    // Giải phóng bộ nhớ và thoát
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(characterTexture1);
    SDL_DestroyTexture(characterTexture2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
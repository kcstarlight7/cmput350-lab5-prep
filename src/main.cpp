#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>
#include <random>
#include <vector>
#include <math.h>
#include <cmath>

#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int FPS_LIMIT = 30;
const float PI = 3.14159;
float FRAME = 0;
int FLAG = 0;

// global tween function
std::function<float(float, float, float)> tween = [](float a, float b, float t) {
    return (1 - t) * a + t * b;
};

// ease in quadratic from lecture
std::function<float(float, float, float)> tween2 = [](float a, float b, float t) {
    return (1 - (t * t)) * a + (t * t) * b;
};

std::function<float(float)> easeinsine = [](float frame) {
    return (1 - cos((frame/30) * PI / 2)) ;
};

std::function<float(float)> easeoutsine = [](float frame) {
    return (cos(((1 / frame) * PI) / 2));
};

std::function<float(float)> easeinoutsine = [](float frame) {
    return (- (cos(PI*(1/frame) - 1))/2);
};

std::function<float(float)> easeoutquad = [](float frame) {
    return (1 - (1 - (1/frame)) * (1 - (1/frame)));
};

std::function<float(float)> easeincubic = [](float frame) {
    return ((1 / frame) * (1 / frame) * (1 / frame));
};

std::function<float(float)> easeoutcubic = [](float frame) {
    return (1 - ((1 / frame) * (1 / frame) * (1 / frame)));
};

std::function<float(float)> easeinquart = [](float frame) {
    return ((1 / frame) * (1 / frame) * (1 / frame) * (1 / frame));
};

std::function<float(float)> easeoutquart = [](float frame) {
    return (1 - ((1 / frame) * (1 / frame) * (1 / frame) * (1 / frame)));
};

void handleInput(sf::Window& window, bool& shouldQuit) {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
            shouldQuit = true;
        }

        // ====== ====== ======
        // TODO: (Q2)
        //  implement key presses (1-9) that replace the tween function
        //  with different alternate tween functions.
        //  Functions can be from lecture or from https://easings.net/#
        // ====== ====== ======
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scan::Num1) {
                FLAG = 1;
            }
            if (keyPressed->scancode == sf::Keyboard::Scan::Num2) {
                FLAG = 2;
            }
            if (keyPressed->scancode == sf::Keyboard::Scan::Num3) {
                FLAG = 3;
            }
            if (keyPressed->scancode == sf::Keyboard::Scan::Num4) {
                FLAG = 4;
            }
            if (keyPressed->scancode == sf::Keyboard::Scan::Num5) {
                FLAG = 5;
            }
            if (keyPressed->scancode == sf::Keyboard::Scan::Num6) {
                FLAG = 6;
            }
            if (keyPressed->scancode == sf::Keyboard::Scan::Num7) {
                FLAG = 7;
            }
            if (keyPressed->scancode == sf::Keyboard::Scan::Num8) {
                FLAG = 8;
            }
            if (keyPressed->scancode == sf::Keyboard::Scan::Num9) {
                FLAG = 9;
            }
        }
    }
}

void render(sf::RenderWindow& window) {
    // Clear with blue background (sky)
    window.clear(sf::Color::Black);
    // ====== ====== ======
    // TODO: (Q1) Draw circle that moves between
    // the left/right half of the screen.
    // Movement should be governed by the tween function.
    // ====== ====== ======
    sf::CircleShape circle;
    circle.setFillColor(sf::Color::Red);
    circle.setRadius(30);
    if (FLAG == 0) {
        circle.setPosition({tween(0, 20, FRAME), WINDOW_HEIGHT / 3});
    } else if (FLAG == 1) {
        circle.setPosition({tween2(0, 1, FRAME), WINDOW_HEIGHT / 3});
    } else if (FLAG == 2) {
        circle.setPosition({easeinsine(FRAME) * WINDOW_WIDTH, WINDOW_HEIGHT / 3});
    } else if (FLAG == 3) {
        circle.setPosition({easeoutsine(FRAME) * WINDOW_WIDTH, WINDOW_HEIGHT / 3});
    } else if (FLAG == 4) {
        circle.setPosition({easeinoutsine(FRAME) * WINDOW_WIDTH, WINDOW_HEIGHT / 3});
    } else if (FLAG == 5) {
        circle.setPosition({easeoutquad(FRAME) * WINDOW_WIDTH, WINDOW_HEIGHT / 3});
    } else if (FLAG == 6) {
        circle.setPosition({easeincubic(FRAME) * WINDOW_WIDTH, WINDOW_HEIGHT / 3});
    } else if (FLAG == 7) {
        circle.setPosition({easeoutcubic(FRAME) * WINDOW_WIDTH, WINDOW_HEIGHT / 3});
    } else if (FLAG == 8) {
        circle.setPosition({easeinquart(FRAME) * WINDOW_WIDTH, WINDOW_HEIGHT / 3});
    } else if (FLAG == 9) {
        circle.setPosition({easeoutquart(FRAME) * WINDOW_WIDTH, WINDOW_HEIGHT / 3});
    }
    
    window.draw(circle);

    // ====== ====== ======
    // TODO: (Q3) Draw tween function graph with a dot
    // on the current portion of the curve
    // ====== ====== ======
    sf::RectangleShape yaxis;
    yaxis.setFillColor(sf::Color::White);
    yaxis.setSize({2, 300});
    yaxis.setPosition({50, 450});
    window.draw(yaxis);
    sf::RectangleShape xaxis;
    xaxis.setFillColor(sf::Color::White);
    xaxis.setSize({700, 2});
    xaxis.setPosition({50, 750});
    window.draw(xaxis);
    sf::CircleShape dot;
    dot.setFillColor(sf::Color::Cyan);
    dot.setRadius(5);
    dot.setOrigin({5, 5});
    float dot_x = 50 + 700 / 30 * FRAME;
    float dot_y = 740 + tween(10, 0, FRAME);
    if (FLAG == 0) {
        dot_y = 740 + tween(10, 0, FRAME);
    } else if (FLAG == 1) {
        dot_y = 740 + tween2(0.3, 0, FRAME);
    } else if (FLAG == 2) {
        dot_y = 740 + easeinsine(FRAME) * -300;
    } else if (FLAG == 3) {
        dot_y = 740 + easeoutsine(FRAME) * -300;
    } else if (FLAG == 4) {
        dot_y = 740 + easeinoutsine(FRAME) * -300;
    } else if (FLAG == 5) {
        dot_y = 740 + easeoutquad(FRAME) * -300;
    } else if (FLAG == 6) {
        dot_y = 740 + easeincubic(FRAME) * -300;
    } else if (FLAG == 7) {
        dot_y = 740 + easeoutcubic(FRAME) * -300;        
    } else if (FLAG == 8) {
        dot_y = 740 + easeinquart(FRAME) * -300;
    } else if (FLAG == 9) {
        dot_y = 740 + easeoutquart(FRAME) * -300;
    }
    dot.setPosition({dot_x, dot_y});
    std::cout << FRAME << std::endl;
    std::cout << dot_x;
    std::cout << " ";
    std::cout << dot_y << std::endl;
    window.draw(dot);

    for (float i = 0; i <= 30; i++) {
        sf::CircleShape graph_dot;
        graph_dot.setFillColor(sf::Color::Yellow);
        graph_dot.setRadius(2.0f);
        graph_dot.setOrigin({2.0f, 2.0f});
        float gdot_x = 50 + 700 / 30 * i;
        float gdot_y = 740 + tween(10, 0, i);
        if (FLAG == 0) {
            gdot_y = 740 + tween(10, 0, i);
        } else if (FLAG == 1) {
            gdot_y = 740 + tween2(0.3, 0, i);
        } else if (FLAG == 2) {
            gdot_y = 740 + easeinsine(i) * -300;
        } else if (FLAG == 3) {
            gdot_y = 740 + easeoutsine(i) * -300;
        } else if (FLAG == 4) {
            gdot_y = 740 + easeinoutsine(i) * -300;
        } else if (FLAG == 5) {
            gdot_y = 740 + easeoutquad(i) * -300;
        } else if (FLAG == 6) {
            gdot_y = 740 + easeincubic(i) * -300;
        } else if (FLAG == 7) {
            gdot_y = 740 + easeoutcubic(i) * -300;
        } else if (FLAG == 8) {
            gdot_y = 740 + easeinquart(i) * -300;
        } else if (FLAG == 9) {
            gdot_y = 740 + easeoutquart(i) * -300;
        }
        graph_dot.setPosition({gdot_x, gdot_y});
        window.draw(graph_dot);
    }

    FRAME++;
    if (FRAME > 30) {
        FRAME = 0;
    }

    window.display();
}

int main() {
    sf::RenderWindow window;

    try {
        // Initialize window
        window.create(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Tween");
        window.setFramerateLimit(FPS_LIMIT);
        // Prevent key repeats.
        window.setKeyRepeatEnabled(false);

        bool shouldQuit = false;
        // Main game loop
        while (window.isOpen()) {
            handleInput(window, shouldQuit);
            if (shouldQuit) {
                break;
            }
            render(window);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}

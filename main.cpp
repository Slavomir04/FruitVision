
#include "src/App/App.h"

using namespace std;
int main()
{

    float alpha = 0.76f;
   App app(sf::VideoMode::getDesktopMode().width * alpha,sf::VideoMode::getDesktopMode().height * alpha,"App");
   app.vStart();

}

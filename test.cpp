<<<<<<< HEAD
#include "sl.h"

int main(int args, char *argv[])
{
  // set up our window and a few resources we need
  slWindow(400, 400, "Simple SIGIL Example", false);
  slSetFont(slLoadFont("ttf/white_rabbit.ttf"), 24);
  slSetTextAlign(SL_ALIGN_CENTER);
  int tex = slLoadTexture("png/glow.png");

  while(!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
  {
    // background glow
    slSetForeColor(0.1, 0.9, 0.2, 0.4);  
    slSprite(tex, 200, 240, 300, 200);

    // large text and fat line
    slSetForeColor(0.0, 0.8, 0.2, 1.0);
    slSetFontSize(24);
    slText(200, 250, "SIGIL:");
    slRectangleFill(200, 240, 100, 7);

    // smaller subtext
    slSetFontSize(14);
    slText(200, 220, "Sprites, text, sound, input, and more!");
    slLine(48, 210, 352, 210);

    slRender();    // draw everything
  }
  slClose();       // close the window and shut down SIGIL
  return 0;
}
=======
<<<<<<< HEAD
#include <bits/stdc++.h>
using namespace std;
auto slice__(auto d,auto f=0,auto g=0){
	auto s=d.size();
	if (f<0){
		f+=s;
	}
	if (g>0){
		g-=s;
	}
	return decltype(d)(d.begin()+f,d.end()+g);
}
int main(){
	cout<<<<endl;
}
=======
#pragma GCC optimize("Ofast")
#define fast_int
#include "pony.hpp"
using namespace std;
___main main(){
	cout<<*(range(inf(12)).begin())<<endl;
}
>>>>>>> c9a875decfb68e9dbd4a0bd5db0f69d080ab2f3b
>>>>>>> 73c96fc9998973e85b92adb8ba49704d7c98dc20

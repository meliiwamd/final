#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL_ttf.h>


using namespace std;

int main();


int velocity = 0;

int score = 0;

int candyscore = 0;

bool jump=false;
bool rectmovedown=false;
bool quit = false;
bool changeplatforms=false;
bool plarformdown=false;
bool gameover=false;
bool change_back=false;

const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL ); 

SDL_Texture* loadTexture( std::string path );



//The sound effects that will be used



SDL_Texture* menu_texture = NULL;	

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

SDL_Texture* gTexture = NULL ;

SDL_Texture* plattexture = NULL;

SDL_Rect platformRect;

SDL_Rect platform2Rect;

SDL_Rect wallb_rect;

SDL_Rect wallt_rect;

SDL_Texture* owl_texture = NULL;

SDL_Texture* wallb_texture = NULL;

SDL_Texture* candytexture = NULL;
		
SDL_Surface* gcandy = NULL;

SDL_Texture* wallt_texture = NULL;

SDL_Rect owlRect;

SDL_Rect candyRect;

SDL_Texture* mTexture;

SDL_Texture* mTexture2;

TTF_Font *Font = NULL;

SDL_Texture *Texture;

SDL_Rect renderQuad3;

SDL_Texture* tscore = NULL;

SDL_Rect scorerect;

SDL_Texture* owl2_texture;

SDL_Rect owl2rect;

SDL_Texture* candy2_texture;

SDL_Rect candy2rect;




SDL_Event e;

bool up=true;



int rand_hight()
{
	int y_position = (rand()%(230))+150;
	return y_position;
}

int rand_hight2()
{
	int c = (rand() % 100) + 50;
	return c;
}
void touching()
{

	bool touch = 0;
	if (owlRect.y + 60 < platform2Rect.y || owl2rect.y + 60 < platform2Rect.y)
	{
		touch = 1;
	}
	if((platform2Rect.y-owlRect.y-90<=velocity*(-1) || platform2Rect.y-owl2rect.y-90<=velocity*(-1)) && touch)
	{
		velocity=0;
		owlRect.y = platform2Rect.y - 70;
		owl2rect.y = platform2Rect.y - 70;
		rectmovedown=true;
	}
}

void jumping()
{
	
	if( e.type == SDL_KEYDOWN)
    {
    	if( currentKeyStates[ SDL_SCANCODE_SPACE ] )
    	{
    		velocity ++;
    	}
    }else if(velocity!=0) jump=true;
}
	
int hight = 5;

void touch_candy()
{
	
	if(owlRect.y < candyRect.y ){
		
		candytexture = NULL;
		
		candyscore ++;

		//cout << candyscore <<endl ;
		
		
		
	}

}

void showcandy(){
	
		gcandy =  IMG_Load( "candy.png");
		candytexture = SDL_CreateTextureFromSurface( gRenderer, gcandy );
		candyRect.x = 220;
		candyRect.y = rand_hight2();
		candyRect.w = 40;
		candyRect.h = 40;	
}

void move(){
	
	if(up){
       	velocity -= 1;
		owlRect.y -= velocity;
		owl2rect.y -= velocity;

		touch_candy();
		if(owlRect.y < 0 || owl2rect.y < 0) gameover = true ;
		if(velocity==0) up = false;
	} else {
		velocity-=1;
		owlRect.y-=velocity;
		owl2rect.y-=velocity;
		if(!up && velocity != 0 && (owlRect.y > 640 || owl2rect.y > 640) ) gameover=true;
		touching();
	}
}
																																																
void game_over()
{
		SDL_Texture* gameover_texture = NULL;

		SDL_Surface* gameoversurface =  IMG_Load( "images.bmp");

		gameover_texture = SDL_CreateTextureFromSurface( gRenderer, gameoversurface);

		SDL_Rect gameoverrect={0,0,480,640};

		SDL_RenderClear(gRenderer);																							
		SDL_RenderCopy( gRenderer, gameover_texture, NULL, &gameoverrect);
		SDL_RenderPresent( gRenderer );	
}

void startmenu()
{
		

		SDL_Surface* menusurface =  IMG_Load( "startmenu.bmp");

		menu_texture = SDL_CreateTextureFromSurface( gRenderer, menusurface);

		SDL_Rect menurect={0,0,480,640};

		SDL_RenderClear(gRenderer);																							
		SDL_RenderCopy( gRenderer, menu_texture, NULL, &menurect);
		SDL_RenderPresent( gRenderer );	
}

void plarform_down()
{
	platformRect.y += 10;
	if(platformRect.y>640) 
		plarformdown=false;
}																																																																																																																																																																																																																																																																																																																																																						

void platform2down(){
	
	platform2Rect.y+=2;
	owlRect.y+=2;
	owl2rect.y+=2;
	if(platform2Rect.y>=450) {
		
		platform2Rect.y=450;
		owlRect.y = platform2Rect.y - 70;
		owl2rect.y = platform2Rect.y - 70;
		int c =rand()%10;
		if(c< 7)
			showcandy();
		up=true;
		changeplatforms=true;
		
		
	}

}

void switchplatforms(){
	platformRect=platform2Rect;
	owlRect.y = platformRect.y - 70;
	owl2rect.y = platformRect.y - 70;
	platform2Rect.x = 120;
	platform2Rect.y = rand_hight();
	platform2Rect.w = 240;
	platform2Rect.h = 50;
	changeplatforms=false;
	jump=false;
	rectmovedown=false;
	score++;
	cout << score << endl;
	
}


//Screen dimension constants
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 640;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

void close();

// void scoretext()
// {
// 	TTF_Init();

// 	TTF_Font * font = TTF_OpenFont("lazy.ttf", 25);

// 	TTF_CloseFont(font);

// 	SDL_Color color = { 255, 255, 255 };
// 	SDL_Surface * surface = TTF_RenderText_Solid(font,"score", color);
// 	SDL_Texture * texture = SDL_CreateTextureFromSurface(gRenderer, surface);
// 	SDL_DestroyTexture(texture);
// SDL_FreeSurface(surface);
// 	SDL_RenderPresent(gRenderer);
// 	int texW = 40;
// 	int texH = 40;
// 	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
// 	SDL_Rect dstrect = { 300, 400, texW, texH };
// 	SDL_RenderCopy(gRenderer, texture, NULL, &dstrect);
// }




bool init()
{
	//Initialization flag
	bool success = true;

	
	

		
		gWindow = SDL_CreateWindow( "Owl Can't Sleep", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		
			
		gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );

				
		int imgFlags = IMG_INIT_PNG;

		SDL_Surface* gplatform =  IMG_Load( "grass.png");
		plattexture = SDL_CreateTextureFromSurface( gRenderer, gplatform );
		
		SDL_Surface* owl_platform =  IMG_Load( "owl.png");
		owl_texture = SDL_CreateTextureFromSurface( gRenderer, owl_platform );

		SDL_Surface* owl2 =  IMG_Load( "owl2.png");
		owl2_texture = SDL_CreateTextureFromSurface( gRenderer, owl2 );

		SDL_Surface* wall_bottom =  IMG_Load( "negartigh.png");
		wallb_texture = SDL_CreateTextureFromSurface( gRenderer, wall_bottom );

		SDL_Surface* wall_top = IMG_Load( "melikatiq.png");
		wallt_texture = SDL_CreateTextureFromSurface( gRenderer, wall_top );

		SDL_Surface* gscore = IMG_Load( "images.png");
		tscore = SDL_CreateTextureFromSurface( gRenderer, gscore );

		SDL_Surface* candy2 = IMG_Load( "candy.png");
		candy2_texture = SDL_CreateTextureFromSurface( gRenderer, candy2 );

		
		platformRect.x = 120;
		platformRect.y = 500;
		platformRect.w = 240;
		platformRect.h = 50;
		
		platform2Rect.x = 120;
		platform2Rect.y = rand_hight();
		platform2Rect.w = 240;
		platform2Rect.h = 50;

		owlRect.x = 190;
		owlRect.y = platformRect.y-70;
		owlRect.w = 80;
		owlRect.h = 100;

		owl2rect.x = 190;
		owl2rect.y = platformRect.y-70;
		owl2rect.w = 80;
		owl2rect.h = 100;

		wallt_rect.x = 0;
		wallt_rect.y = 560;
		wallt_rect.w = 480;
		wallt_rect.h = 30;

		wallb_rect.x = 0;
		wallb_rect.y = 50;
		wallb_rect.w = 480;
		wallb_rect.h = 30;

		scorerect.x = 0;
		scorerect.y = 0;
		scorerect.h = 50;
		scorerect.w = 100;

		candy2rect.x = 360;
		candy2rect.y = 10;
		candy2rect.h = 40;
		candy2rect.w = 40;

		

	
	
	
	// quit SDL_mixer

		

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	
	gTexture = loadTexture( "sky1.bmp" );

	
	
	
	

	return success;
}

void close()
{
	//Free loaded image
	SDL_DestroyTexture( gTexture );
	gTexture = NULL;

	

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	
}

SDL_Texture* loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	
    newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );

	SDL_FreeSurface( loadedSurface );
	

	return newTexture;
}



int main(  )
{

	srand(time(0));
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else

	{
		loadMedia();

		startmenu();
		SDL_Delay(2000);		
			//Main loop flag
			

			//Event handler
			
			

			//main while 
			while( !quit )
			{
				 
				if( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					if (e.type == SDL_KEYDOWN){
						switch(e.key.keysym.sym){
							{
							 case SDLK_UP:
							
							if(!jump){
					
								velocity +=2;
							}
							break;
							case SDLK_SPACE: 
								
							jump=true;

							plarformdown=true;
							}
							
						 }

					}
					
				}
				

				


				if(!gameover){
					// if()
					// startmenu();
					// SDL_Delay(1000);
					// menu_texture = NULL;
					if(score > 2 && score <10)
						gTexture = loadTexture( "sky2.bmp" );
					if(score >=10 )
						gTexture = loadTexture( "skynight.bmp" );
					if(jump){
						if(!rectmovedown){
							move();		

						}
						else{
							platform2down();
							if(changeplatforms)
								switchplatforms();
						}
					}


				if(plarformdown) plarform_down(); 
				
				SDL_SetRenderDrawColor(gRenderer,255,255,255,255);
				
				SDL_RenderClear(gRenderer);
				
				SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );

				SDL_RenderCopy( gRenderer, plattexture,NULL , &platformRect );
			
				SDL_RenderCopy( gRenderer, plattexture,NULL , &platform2Rect );

				
						
					
					if(currentKeyStates[ SDL_SCANCODE_RIGHT ]) SDL_RenderCopy(gRenderer , owl_texture , NULL ,&owlRect);
					

							
					if(currentKeyStates[ SDL_SCANCODE_LEFT ])  SDL_RenderCopy(gRenderer , owl2_texture , NULL ,&owl2rect);	
							
				
				SDL_RenderCopy( gRenderer, candytexture, NULL, &candyRect);

				SDL_RenderCopy( gRenderer, wallb_texture, NULL , &wallb_rect);

				SDL_RenderCopy( gRenderer, wallt_texture, NULL, &wallt_rect);

				

				SDL_Rect fillRect = { 0, 0, SCREEN_WIDTH, 50 }; 

				SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 255 );

				SDL_RenderFillRect( gRenderer, &fillRect );

				SDL_Rect fillRect2 = { 0, 590, SCREEN_WIDTH, 50 }; 

				SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 255 );

				SDL_RenderFillRect( gRenderer, &fillRect2 );

				SDL_RenderCopy( gRenderer, tscore, NULL, &scorerect);

				SDL_RenderCopy( gRenderer, candy2_texture, NULL, &candy2rect);
				//SDL_RenderCopyEx(gRenderer , Texture , NULL , &renderQuad3 , 0.0 , NULL , SDL_FLIP_NONE);


				// SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, 0.0 , center, flip );
				
				// SDL_RenderCopyEx( gRenderer, mTexture2, clip, &renderQuad2, 0.0 , center, flip );



				
				//Update screen
				SDL_RenderPresent( gRenderer );
				SDL_Delay(30);
				}
				else{
					game_over();
					SDL_Delay(3000);
					gameover = false;
					jump=false;
					rectmovedown= true;
					quit = false;
					changeplatforms=false;
					plarformdown = false;

					platformRect.x = 120;
					platformRect.y = 500;
					platformRect.w = 240;
					platformRect.h = 50;
					
					owlRect.x = 190;
					owlRect.y = platformRect.y-90;
					owlRect.w = 80;
					owlRect.h = 100;

					velocity = 0;
					score = 0;
					//change_back=false;
					//close();


					
					//replay();
				}
				
			}
		}
	

	//Free resources and close SDL
	close();

	return 0;
}
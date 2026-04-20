#include "Renderer.h"




#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) glClearError();\
        x;\
        ASSERT(glLogCall(#x, __FILE__, __LINE__) )

ImFont* Renderer::upheav = nullptr;
ImFont* Renderer::gameFont = nullptr;
ImFont* Renderer::minecraftFont = nullptr;
ImFont* Renderer::marioFont = nullptr;
ImFont* Renderer::marioFontsmall = nullptr;
ImFont* Renderer::pixer = nullptr;

ma_sound Renderer::MENU_SOUND;
ma_sound Renderer::GAME_OVER_SOUND;
ma_sound Renderer::CARD_FLIP;
ma_sound Renderer::CARDS_GAIN;
ma_sound Renderer::CORRECT_ANSWER;
ma_sound Renderer::INVALID_ANSWER;
ma_sound Renderer::DAMAGE;
ma_sound Renderer::EXPLOSION;
ma_sound Renderer::FUSE;
ma_sound Renderer::GAIN_TIME;
ma_sound Renderer::LASER;
ma_sound Renderer::POWER_UP;
ma_sound Renderer::TIMER;
ma_sound Renderer::CAKE_SPAWN;

Renderer::~Renderer()
{

	Shaders::destroyShaders();
	Textures::cleanUpTextures();
	ImGui_ImplOpenGL3_Shutdown();  // Cerrar el backend de OpenGL
	ImGui_ImplGlfw_Shutdown();     // Cerrar el backend de GLFW

	
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
}
void Renderer::toggleFullscreen() {
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	vec2 windowPos = vec2(0, 0);
	if (isFullscreen == false) {
		windowSize.x = (float)(mode->width);
		windowSize.y = (float)(mode->height);
		isFullscreen = true;
	} else {
		windowSize.x = (float)mode->width / 2;
		windowSize.y = (float)mode->height / 2;
		
	    windowPos = vec2(mode->width/6, mode->height/6);
		monitor = NULL;
		isFullscreen = false;
	}
	aspectRatio = windowSize.x / windowSize.y;
	glfwSetWindowMonitor(window, monitor, windowPos.x, windowPos.y, (int)windowSize.x, (int)windowSize.y, mode->refreshRate);
	glViewport(0, 0, (int)windowSize.x, (int)windowSize.y);
	glfwSwapInterval(1);//Vysinc
}

void loadSound(const char* path, ma_sound* sound){
	soundResult = ma_sound_init_from_file(&soundEngine, path, 0, NULL, NULL, sound);
    if (soundResult != MA_SUCCESS) {
		printf("Error al cargar el sonido: %s\n", path);
	} else {
		printf("Sonido cargado exitosamente: %s\n", path);
	}
}

bool Renderer::initRenderer(bool fullscreen)
{
	const char* a = "HJ"; //se puede alterar el pointer a char* pero no a lo que a punta
	 //No se puede alterar el pointer a char* ni a lo que apunta, es decir, es un pointer constante a char constante.
	// es un pointer a un char constane.
	char b[] = "as"; //Es un pointer constante a chars modificables

	loadSound("assets/sounds/cakeSpawn.wav", &Renderer::CAKE_SPAWN);
	loadSound("assets/sounds/cardFlip.mp3", &Renderer::CARD_FLIP);
	loadSound("assets/sounds/cardsGain.wav", &Renderer::CARDS_GAIN);
	loadSound("assets/sounds/correctAnswer.wav", &Renderer::CORRECT_ANSWER);
	loadSound("assets/sounds/damage.mp3", &Renderer::DAMAGE);
	loadSound("assets/sounds/explosion.wav", &Renderer::EXPLOSION);
	loadSound("assets/sounds/fuse.wav", &Renderer::FUSE);
	loadSound("assets/sounds/gainTimeAudio.mp3", &Renderer::GAIN_TIME);
	loadSound("assets/sounds/gameOverSound.wav", &Renderer::GAME_OVER_SOUND);
	loadSound("assets/sounds/invalid.WAV", &Renderer::INVALID_ANSWER);
	loadSound("assets/sounds/laser.mp3", &Renderer::LASER);
	loadSound("assets/sounds/menuSound.wav", &Renderer::MENU_SOUND);
	loadSound("assets/sounds/powerUpSound.mp3", &Renderer::POWER_UP);
	loadSound("assets/sounds/timer.wav", &Renderer::TIMER);


	isFullscreen = fullscreen;
	if (!setupWindow()) {
		return false;
	}
	
	GLenum glewInitErr = glewInit();
	if (glewInitErr != GLEW_OK) {
		assert(false && "GLEW init error");
		return false;
	}
	
	//glew config
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST); 
	glDepthMask(GL_TRUE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	
	

	Shaders::initializeShaders();
	Textures::initializeTextures();
	

	int width, height, channels;
	unsigned char* image = stbi_load("assets/textures/mouse.png", &width, &height, &channels, 4);
	if (!image) {
		printf("Error: No se pudo cargar la imagen del cursor\n");
		return false;
	}
	GLFWimage cursorImage;
	cursorImage.width = width;
	cursorImage.height = height;
	cursorImage.pixels = image;

	// Crear un cursor GLFW
 cursor = glfwCreateCursor(&cursorImage, 0, 0); // (0, 0) es el hotspot (esquina superior izquierda)
	stbi_image_free(image); // Liberar la memoria de la imagen

	// Establecer el cursor en la ventana
	glfwSetCursor(window, cursor);
	

	return true;
}
bool Renderer::setupWindow(){

	//Initialize GLFW
	if (!glfwInit()) {
		assert(false && "GLFW init error");
		return false;
	}

	//glfw Config

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_REFRESH_RATE, 120);
    glfwSetErrorCallback(Renderer::errorCallback);

	//Create window
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	if (isFullscreen) {
		windowSize.x = (float)(mode->width);
		windowSize.y = (float)(mode->height);
	}
	else {
		windowSize.x = (float)mode->width / 2;
		windowSize.y = (float)mode->height / 2;
		monitor = NULL;
	}
	
	aspectRatio = windowSize.x / windowSize.y;
	window = glfwCreateWindow((int)windowSize.x, (int)windowSize.y, "Food Arcade", monitor, NULL);

	if (!window) {
		assert(false && "Window INIT error");
		return false;
	}
	//Window Config
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	std::cout << "Renderizador: " << renderer << std::endl;
	std::cout << "Version de openGL soportada: " << version << std::endl;

	int width, height, channels;
	unsigned char* image = stbi_load("assets/textures/burger.png", &width, &height, &channels, 4); // Carga en RGBA (4 canales)
	if (image) {
		GLFWimage images[1];
		images[0].width = width;
		images[0].height = height;
		images[0].pixels = image;
		glfwSetWindowIcon(window, 1, images); // Asignar el �cono a la ventana
		stbi_image_free(image); // Liberar la memoria del �cono
	}
	else {
		printf("Error al cargar el �cono.\n");
	}


	if (!setupImGUI()) {
		return false;
	}

	return true;
}
bool Renderer::setupImGUI() {
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGuiContext* context = ImGui::CreateContext();

	if (!context) {
		assert(false && "ImGui::CreateContext failed!");
		return false;
	}
	
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);

	ImGui_ImplOpenGL3_Init("#version 120");

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
	// - Read 'docs/FONTS.md' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	// - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
	//io.Fonts->AddFontDefault();
	
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    	marioFont = io.Fonts->AddFontFromFileTTF("assets/fonts/marioFont.ttf", 60.0f);
	 minecraftFont = io.Fonts->AddFontFromFileTTF("assets/fonts/MinecraftRegular.ttf", 60.0f);
	 pixer = io.Fonts->AddFontFromFileTTF("assets/fonts/Pixer-Regular.ttf", 60.0f);
	 upheav = io.Fonts->AddFontFromFileTTF("assets/fonts/upheavtt.ttf", 18.0f);
	 gameFont = io.Fonts->AddFontFromFileTTF("assets/fonts/isaacGame.ttf", 36.0f);
	 marioFontsmall = io.Fonts->AddFontFromFileTTF("assets/fonts/marioFont.ttf", 30.0f);
	//IM_ASSERT(font != nullptr)
	//ImGui_ImplOpenGL3_CreateDeviceObjects();
	 io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
	//io.ConfigFlags &= ~ImGuiConfigFlags_NoMouseCursorChange;
	ImGui::GetIO().IniFilename = "assets/GUI/imgui.ini";
	return true;
}

void Renderer::errorCallback(int error, const char* description)
{
	std::cout << "Error: " << error << ": " << description << std::endl;
}
bool Renderer::glLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError()) {
		assert("OpenGL init error");
		std::cout << "[OpenGL error] (" << error << "):" << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}


void Renderer::background( GLfloat r, GLfloat g, GLfloat b) {
	//glClearColor(r, g,b, 1.0f);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::update() {
	glfwSwapBuffers(window);
}





#include "../events/EventHandler.h"
#include <vector>

using namespace std;
class Commands {
public:
    static const int commandsCount = 7
		
		
		
		
		
;

    const static string commands[Commands::commandsCount][2]; 
    static void scaleCommand(std::vector<std::string> input, Camera* camera) {

		if (input.size() == 1) {
			cout << "[Console] Command syntax ----> /tp (value > 0)" << endl;
		}
		else {
			float value = stof(input[1]);
			if (value > 0) {
				camera->setZoom(value);
				cout << "[Console] Succesfully scaled" << endl;
			}
			else {
				cout << "[Console] invalid scale value" << endl;
			}

		}
    };
	
    static void tpCommand(std::vector<std::string> input, Camera* camera) {
		if (input.size() == 1) {
			cout << "[Console] Command syntax ----> /tp posX posY" << endl;
		}
		else {
			float posX = stof(input[1]);
			float posY = stof(input[2]);
			float posZ = stof(input[3]);
			vec3 pos = vec3(posX, posY,posZ);
			camera->setPos(pos);
			cout << "[Console] Succesfully teleported" << endl;

		}
   
    };

	

	
	

	static void processCommands(Simulation* simulation) {
		while (true) { // Mientras no se indique que se debe detener
			if (!commandQueue.empty()) {
				std::string command;
				{
					std::lock_guard<std::mutex> lock(queueMutex);
					command = commandQueue.front();
					commandQueue.pop();
				}
				if (!command.empty() && command[0] == '/') {//preguntamos si uso /
					try {
						command.erase(0, 1);
						if (command.empty()) {
							throw runtime_error("empty command");
						}
						std::vector<std::string> inputSplited = Commands::split(command, " ");

						//if de preguntar que comandos es
						if ((inputSplited[0]) == Commands::commands[0][0]) {//TP COMMAND
							Commands::tpCommand(inputSplited,simulation->camera);
						}
						else if (inputSplited[0] == Commands::commands[1][0]) { //HELP COMMAND
							for (int i = 0; i < Commands::commandsCount; ++i) {
								cout << " ----> /" + Commands::commands[i][0] + " - " + Commands::commands[i][1] << endl;
							}
						}
						else if (inputSplited[0] == Commands::commands[2][0]) { // SCALE COMMAND
							Commands::scaleCommand(inputSplited,simulation->camera);
						}
						else if (inputSplited[0] == Commands::commands[3][0]) { //show fps
							showFps = !showFps;
							cout << "[Console] rule succesfully updated" << endl;
						}
					
						
					
						else if (inputSplited[0] == Commands::commands[10][0]) {
							simulation->camera->shader->loadShader();
							cout << "[Console] Shader succesfully reloaded" << endl;
						}
						else if (inputSplited[0] == Commands::commands[11][0]) {
							mouseScalling = !mouseScalling;
							cout << "[Console] rule succesfully updated" << endl;
						}
						else if (inputSplited[0] == Commands::commands[12][0]) {
							mouseFoving = !mouseFoving;
							cout << "[Console] rule succesfully updated" << endl;
						}
						else {  /*termina el if de preguntar que comando es*/
							cout << "[Console] command cannot be ressolved" << endl;
						} 
					}
					catch (exception& e) {
						cout << "[Console] Invalid command syntax" << endl;
					}
				}
				else { //caso no usar     -> /
					cout << "[Console] Invalid syntax, commands must start with (/)" << endl;

				}
				cout << "> ";
			} /*caso no halla nada en cola */else {
				break;
			}
		}
	}
    static std::vector<std::string> split(std::string& text,const char* split) {
      
        size_t size = text.size();
        std::vector<std::string> strings;
        int copyStart = 0;
        for (int i = 0; i < size; ++i) {
            if (text[i] == *split) {
                std::vector<char> chars;
                for (int j = copyStart; j < i; ++j) {
                    chars.push_back(text[j]);
                }
                
                if (chars.size() != 0) {
                    chars.push_back('\0');
                    std::string s(chars.data());
                    strings.push_back(s);
                }
               
                copyStart = i + 1;

            }
           
               
        }
        std::vector<char> chars;
        for (int j = copyStart; j < size;++j) {
            chars.push_back(text[j]);
        }
        if (chars.size() != 0) {
            chars.push_back('\0');
            std::string s(chars.data());
            strings.push_back(s);

        }
        return strings;
    }
};
const std::string Commands::commands[Commands::commandsCount][2] {
    {"tp", "teleport the camera"},
    { "help","Say the list of commands" },
    { "scale", "changes de zoom of the camera" },
    { "fps", "toggles fps showing" },

	
	{ "reloadShader", "reloads shaders"},
	{ "toggleMouseScalling", "enables/dissables mouseScalling"},
	{ "toggleMouseFoving", "enables/dissables mouseFoving"}};
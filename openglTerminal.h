#define BOTH			0
#define OPENGL			1
#define COUT			2

class openglTerminal
{
	public:
		
		void print(char text[100], int type);
		void input(char text[100]);
		void showLines(void);
};

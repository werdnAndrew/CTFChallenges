#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGS_COUNT 4
unsigned regs[REGS_COUNT];

unsigned programInstr[] = {0x1064, 0x11C8, 0x2201, 0x4000, 0x1234, 0x6000, 0x5000, 0x1234, 0x7000, 0x8000, 0x0000};

//vm stops when running = 0
int isRunning = 1;

//User input
char *userInput = NULL;
char *userName = NULL;
char *userLicense = NULL;

// instruction fields 
int instrNum = 0;
int op1 = 0;
int op2 = 0;
int op3 = 0;
int immValue  = 0;

//Program Counter
int pc = 0;

/* fetch the next instruction from programInstr[] */
int fetch(void){
	//the program counter
	//static int pc = 0;
	//printf("Pc is: %d\n", pc);
	return programInstr[pc++];
}

// decode an instruction 
void decode(int instr){
  instrNum = (instr & 0xF000) >> 12;
  op1      = (instr & 0x0F00) >>  8;
  op2      = (instr & 0x00F0) >>  4;
  op3      = (instr & 0x000F);
  immValue      = (instr & 0x00FF);
}

// run the decoded instruction 
void execute(void){
	switch(instrNum){
		case 0:
    		// stops execution of vm
    		isRunning = 0;
    		break;
    	case 1:
    		// Load value into register 
    		regs[op1] = immValue;
    		break;
    	case 2:
    		//add
    		regs[op1] = regs[op2] + regs[op3];
    		break;
    	case 3: ;
			
			int currentChar;
			size_t size = 0;
			size_t length = 0;

			while ((currentChar=getchar()) != EOF && currentChar != '\n'){
				if (length + 1 >= size){
					size += 10;
					userInput = realloc(userInput, sizeof(char)*size);
				}
				userInput[length++] = currentChar;
			}
			if (userInput != NULL){
				userInput[length] = '\0';			
			}
    		break;  
		case 4:
			printf("Please enter your Username: ");
			programInstr[pc] = 0x3000;
			break;    
		case 5:
			printf("Please enter your Password: ");
			programInstr[pc] = 0x3002;
			break;
		case 6:
			userName = (char*)malloc(size);
			strcpy(userName, userInput);
			break;
		case 7:
			userLicense = (char*)malloc(size);
			strcpy(userLicense, userInput);
			break;
		case 8:
			//License key algorithm
			//memfrob

			for (int i = 0; i < strlen(userName); i ++){
				userName[i] ^= 42;	
				//printf("Char before XOR is: %c\n", userName[i]);
			}

			printf("XOR string: %s\n", userName);

			for (int i = 0; i < strlen(userName); i ++){
				userName[i] ^= 42;	
				//printf("Char after XOR is: %c\n", userName[i]);
			}

			printf("XOR string: %s\n", userName);

			//memfrob(userLicense, size);
			break;
		case 9: 
			//False License key algorithm
			break;
		case 10:
			//Either third algorithm or comparison method 1
			break;
		case 11:
			break;

  }
}

// display all registers
void showRegs(void){
	printf("regs = ");
	for(int i = 0; i < REGS_COUNT; i++){
		printf("%04X ", regs[i]);
	}
	printf("\n");
}

void run(void){
	while(isRunning){
		//showRegs();
    	int instr = fetch();
    	decode(instr);
    	execute();
	}
	//showRegs();
}

int main(int argc, const char * argv[]){
	run();
	printf("Username is: %s \n", userName);
	printf("Password is: %s \n", userLicense);
	free(userInput);
	free(userName);
	free(userLicense);
	return 0;
}


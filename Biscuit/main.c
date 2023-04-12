#include "pch.h"
#include "utils.h"
#include "signal_handlers.h"

// Benchmark prog - akc6a6kckciio1kk6iickko1iii6kkciio1kk1

typedef enum LaunchModesEnum
{
	NONE,
	FILE_EXEC,
	SHELL,
	BENCH
} LaunchModes_t;

static VectorContainer_t g_Array;
static int g_iPointerLocation = 0;

static bool g_bExecution = true;

void IfExecute(const char* code, size_t codeLen);
void Arythmetic(const char* code, size_t codeLen);

static inline void MainFileExec();
static inline void MainShell();

#define GetByID(id) (*(int*)(GetElementByID(&g_Array, (id))->m_pObjectPtr))
#define GetByIDPtr(id) ((int*)(GetElementByID(&g_Array, (id))->m_pObjectPtr))

bool EndsWith(const char* const str, const char* const suffix)
{
	const size_t strLen = strlen(str);
	const size_t sufLen = strlen(suffix);
	if (strLen < sufLen) return false;
	return strncmp(&str[strLen - sufLen], suffix, sufLen) == 0;
}

const char* ReadFile(const char* const fileName)
{
	FILE* f = NULL;
	errno_t err = fopen_s(&f, fileName, "r");
	if (err != 0)
	{
		puts("ERROR! File not found!");
		exit(0);
	}

	_fseeki64(f, 0, SEEK_END);
	size_t size = _ftelli64(f);
	char* s = (char*)malloc(sizeof(char) * size);
	assert(s && "malloc error!");
	_fseeki64(f, 0, SEEK_SET);
	fread(s, sizeof(char), size, f);
	return s;
}

void Execute(const char* code, size_t codeLen)
{
	srand(time(NULL));
	int i = 0;
	while (i < codeLen && !g_bInterupted)
	{
		int* pointerData = GetByIDPtr(g_iPointerLocation);

		switch (code[i])
		{
			case 'i':
				if (g_iPointerLocation > 0) g_iPointerLocation -= 1;
				break;
			case 'I':
				if (g_iPointerLocation > 0)
				{
					g_iPointerLocation -= 1;
					*pointerData += GetByID(g_iPointerLocation + 1);
				}
				break;
			case 'k':
				g_iPointerLocation += 1;
				if (g_Array.m_ziSize <= g_iPointerLocation) PushBack(&g_Array, ToPtr(0));
				break;
			case 'K':
				g_iPointerLocation += 1;
				if (g_Array.m_ziSize <= g_iPointerLocation) PushBack(&g_Array, ToPtr(0));
				*pointerData += GetByID(g_iPointerLocation - 1);
				break;
			case 'r':
				{
					char Buff[_MAX_PATH];
					memset(Buff, 0, sizeof(Buff) / sizeof(Buff[0]));

					puts("File Name: ");
#ifdef WIN32
					(void)scanf_s("%s", &Buff[0]);
#else
					(void)scanf("%s", &Buff[0]);
#endif
					if (EndsWith(Buff, ".bc961"))
					{
						const char* fileData = ReadFile(Buff);
						size_t fileDataLen = strlen(fileData);
						Execute(fileData, fileDataLen);
						free((void*)fileData);
					}
					else
					{
						puts("ERROR! Unknown extension.");
						return;
					}
				}
			case 'N':
				g_iPointerLocation = 0;
				break;
			case 'n':
				printf("%i\n", *pointerData);
				break;
			case 'R':
				*pointerData = rand() % 100;
				break;
			case 'c':
				*pointerData += 1;
				break;
			case 'C':
				*pointerData += 10;
				break;
			case 'o':
				if (*pointerData > 0) *pointerData -= 1;
				break;
			case '-':
				g_bExecution = false;
				return;
			case '>':
				puts("");
				break;
			case 'O':
				if (*pointerData > 10) *pointerData -= 10;
				break;
			case 'L':
				*pointerData = 0;
				break;
			case '(':
				{
					int ifend = i + 1;
					int j = 0;
					char to_execute[1024];
					memset(to_execute, 0, sizeof(to_execute) / sizeof(to_execute[0]));
					while (code[ifend] != ')')
					{
						to_execute[j] = code[ifend];
						ifend++;
						i++;
						j++;
					}
					IfExecute(to_execute, strlen(to_execute));
				}
				break;
			case '{':
				{
					int arend = i + 1;
					int j = 0;
					char to_count[1024];
					memset(to_count, 0, sizeof(to_count) / sizeof(to_count[0]));
					while (code[arend] != '}')
					{
						to_count[j] = code[arend];
						arend++;
						i++;
						j++;
					}
					Arythmetic(to_count, strlen(to_count));
				}
				break;
			case 'B':
				if (code[i + 1] == '[')
				{
					int nigg = i + 2;
					int j = 0;
					char filename[_MAX_PATH];
					memset(filename, 0, sizeof(filename) / sizeof(filename[0]));
					while (code[nigg] != ']')
					{
						filename[j] = code[nigg];
						nigg++;
						i++;
						j++;
					}
					const char* filedata = ReadFile(filename);
					const size_t filesize = strlen(filedata);
					Execute(filedata, filesize);
					free((void*)filedata);
				}
				else
				{
					// File not found
					puts("ERROR! File not found!");
				}
				break;
			case '9':
				putc((char)*pointerData, stdout);
				break;
			case 'a':
				printf("%i %c\n", *pointerData, (char)*pointerData);
				break;
			case 'e':
				{
					int y;
#ifdef WIN32
					int readed = scanf_s("%i", &y);
#else
					int readed = scanf("%i", &y);
#endif
					if (!readed) y = 0;
					*pointerData = y;
				}
				break;
			case '6':
				if (*pointerData == 0)
				{
					int open_braces = 1;
					while (open_braces > 0)
					{
						i += 1;
						if (code[i] == '6')
							open_braces += 1;
						else if (code[i] == '1')
							open_braces -= 1;
					}
				}
				break;
			case '1':
				{
					int open_braces = 1;
					while (open_braces > 0)
					{
						i -= 1;
						if (code[i] == '6')
							open_braces -= 1;
						else if (code[i] == '1')
							open_braces += 1;
					}
					i -= 1;
				}
				break;
			default:
				break;
		}
		i += 1;
	}
	g_bInterupted = false;
	puts(" ");
}

void Arythmetic(const char* code, size_t codeLen)
{
	int nums[2];
	memset(nums, 0, sizeof(nums) / sizeof(nums[0]));

	VectorContainer_t actions;
	memset(&actions, 0, sizeof(actions));
	actions.m_ziTypeSize = sizeof(int);

	int pointer = 0;
	bool hasAction = false;

	for (int i = 0; i < codeLen; i++)
	{
		switch (code[i])
		{
			case 'k':
				nums[pointer] = GetByID(g_iPointerLocation + 1);
				pointer += 1;
				break;
			case 'i':
				nums[pointer] = GetByID(g_iPointerLocation - 1);
				pointer += 1;
				break;
			case 't':
				nums[pointer] = GetByID(g_iPointerLocation);
				pointer += 1;
				break;
			case '+':
				PushBack(&actions, ToPtr(1));
				hasAction = true;
				break;
			case '-':
				PushBack(&actions, ToPtr(0));
				hasAction = true;
				break;
			case '*':
				PushBack(&actions, ToPtr(2));
				hasAction = true;
				break;
			case '%':
				PushBack(&actions, ToPtr(3));
				hasAction = true;
				break;
			default:
				break;
		}
	}

	if (hasAction == true)
	{
		switch (*(int*)(GetElementByID(&actions, 0)->m_pObjectPtr))
		{
			case 0:
				if (nums[0] > nums[1])
					GetByID(g_iPointerLocation) = nums[0] - nums[1];
				else
					putc('0', stdout);
				break;
			case 1:
				GetByID(g_iPointerLocation) = nums[0] + nums[1];
				break;
			case 2:
				GetByID(g_iPointerLocation) = nums[0] * nums[1];
				break;
			case 3:
				GetByID(g_iPointerLocation) = nums[0] / nums[1];
				break;
			default:
				break;
		}
	}
	else
	{
		puts("ERROR! Action not found!");
		exit(0);
	}

	Clear(&actions);
}

void IfExecute(const char* code, size_t codeLen)
{
	int nums[2];
	memset(nums, 0, sizeof(nums) / sizeof(nums[0]));

	int action = 0;
	int pointer = 0;
	bool ends = false;
	char execute[1024];
	memset(execute, 0, sizeof(execute) / sizeof(execute[0]));

	for (int i = 0; i < codeLen; i++)
	{
		switch (code[i])
		{
			case 'i':
				nums[pointer] = GetByID(g_iPointerLocation - 1);
				pointer += 1;
				break;
			case 'k':
				nums[pointer] = GetByID(g_iPointerLocation + 1);
				pointer += 1;
				break;
			case 't':
				nums[pointer] = GetByID(g_iPointerLocation);
				pointer += 1;
				break;
			case '>':
				action = 1;
				break;
			case '<':
				action = 2;
				break;
			case '=':
				action = 0;
				break;
			case '~':
				action = 3;
				break;
			case '!':
				{
					int j = 0;
					for (char* ptr = &((char*)code)[i + 1]; ptr != &code[codeLen - 1]; ptr++, j++)
						execute[j] = *ptr;
					bool anif1 = false;
					bool anif2 = false;
					for (int p = 0; p < strlen(execute); p++)
					{
						if (execute[p] == '(')
						{
							anif1 = true;
							for (int j = 0; j < strlen(execute); j++)
							{
								if (execute[j] == ')') anif2 = true;
							}
						}
					}
					if (anif1 == true && anif2 == false) execute[strlen(execute)] = ')';
					ends = true;
					goto BREAK_FOR;
				}
				break;
			default:
				break;
		}
	}

BREAK_FOR:
	if (ends == true)
	{
		switch (action)
		{
			case 0:
				if (nums[0] == nums[1]) Execute(execute, strlen(execute));
				break;
			case 1:
				if (nums[0] > nums[1]) Execute(execute, strlen(execute));
				break;
			case 2:
				if (nums[0] < nums[1]) Execute(execute, strlen(execute));
				break;
			case 3:
				if (nums[0] != nums[1]) Execute(execute, strlen(execute));
				break;
			default:
				break;
		}
	}
	else
	{
		// No IF body
		puts("ERROR! If without body!");
	}
}

const char* GetLaunchModeString(LaunchModes_t mode)
{
	switch (mode)
	{
		case FILE_EXEC:
			return "File execution";
		case SHELL:
			return "Shell";
		case BENCH:
			return "Benchmark";
		default:
			return "Unknown";
	}
}

static inline void PrintVer(LaunchModes_t mode)
{
	puts("Biscuit v" BISCUIT_VERSION_FULL);
	puts("Build from " __DATE__ ", platform: " BISCUIT_PLATFORM);
	printf("Current mode: %s\n", GetLaunchModeString(mode));
	puts("");
}

int main()
{
	memset(&g_Array, 0, sizeof(g_Array));
	g_Array.m_ziTypeSize = sizeof(int);

	PushBack(&g_Array, ToPtr(0));

	// Setting up signal handlers
	SetSignals();

	LaunchModes_t mode = NONE;
	{
		printf("Mode (1 - file execute, 2 - shell): ");
#ifdef WIN32
		(void)scanf_s("%i", &mode);
#else
		(void)scanf("%i", &mode);
#endif
	}

	PrintVer(mode);

	switch (mode)
	{
		case FILE_EXEC:
			MainFileExec();
			break;
		case SHELL:
			MainShell();
		default:
			break;
	}

	Clear(&g_Array);

	puts("Press any key to exit...");
	(void)_getch();

	return 0;
}

static inline void MainFileExec()
{
	char Buff[_MAX_PATH];
	memset(Buff, 0, sizeof(Buff) / sizeof(Buff[0]));
	puts("File Name: ");
#ifdef WIN32
	(void)scanf_s("%s", &Buff[0]);
#else
	(void)scanf("%s", &Buff[0]);
#endif
	if (EndsWith(Buff, ".bc961"))
	{
		const char* filedata = ReadFile(Buff);
		const size_t filesize = strlen(filedata);
		Execute(filedata, filesize);
		free((void*)filedata);
	}
	else
	{
		puts("ERROR! Unknown extension.");
		return;
	}
}

static inline void MainShell()
{
	while (g_bExecution)
	{
		char code[4096];
		memset(code, 0, sizeof(code) / sizeof(code[0]));
		printf("Code: ");
		(void)getchar(); // For removing \n
#ifdef WIN32
		(void)scanf_s("%4095[^\n]", &code[0], 4096);
#else
		(void)scanf("%4095[^\n]", &code[0]);
#endif
		Execute(code, strlen(code));
	}
}

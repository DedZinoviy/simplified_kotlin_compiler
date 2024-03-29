#include "parser_tab.h"
#include "print_functions.h"
#include "semantic_transformations.h"
#include "iohandler.h"
#include "stdlib.hpp"
#include "attributing.hpp"
#include "generation.hpp"

extern "C" int yyparse();

int main (int argc, char * argv[])
{
if (argc < 2)
	{
		printf("The path to the input file is missing; use -h to get help using the utility.\n");
		return -1;
	}

    int needsDotCon = 0;
    int needsDotFile = 0;
	int needsHelp = 0;
    int opt = 0;

    while((opt = t_getopt(argc, argv, "cfht")) != -1)
    {
        switch(opt) 
        {
            case 'h':
                printf("%s", getHelp());
				needsHelp = 1;
                return 0;
                break;
            case 't':
                needsTokens = 1;
                break;
            case 'c':
                needsDotCon = 1;
                break;
            case 'f':
                needsDotFile = 1;
                break;
            case '?':
                printf("%c : unrecognized option; use -h to get help using the utility.\n", opt);
                return -1;
                break;
        }   
    }
	if (!needsHelp && argv[argc - 1][0] == '-')
	{
		printf("The path to the input file is missing; use -h to get help using the utility.\n");
		return -1;
	}

	setFile(argv[argc - 1]);

    printf("The parsing process has started.\n");

	yyparse();

    printf("The parsing process is completed.\n");

    if (needsDotCon || needsDotFile) 
    {   
        char * res = generateDotFromKotlinFile(root);
        if (needsDotFile)
        {
            FILE *f = fopen("result.gv", "w");
            fprintf(f, "%s", res);
            fclose(f);
        }
        if (needsDotCon)
        {
            printf("%s\n", res);
        }
    
    }

    struct SemanticError * err = NULL;
    err = checkAndAddReturn(root);
    if (err != NULL)
    {
        printf("%s\n", err->errMessage);
        return err->code;
    }
    replaceRTLTypes(root);
    replaceLiteralsToObjects(root);
    replaceOperators(root);

    attributeBaseTypes(root);

    if (needsDotCon || needsDotFile) 
    {   
        char * res = generateDotFromKotlinFile(root);
        if (needsDotFile)
        {
            FILE *f = fopen("result_rep.gv", "w");
            fprintf(f, "%s", res);
            fclose(f);
        }
        if (needsDotCon)
        {
            printf("%s\n", res);
        }
    
    }

    err = checkModifierLists(root);


    if (err != NULL)
    {
        printf("%s\n", err->errMessage);
        return err->code;
    }

    initStdClasses();

    class ClassTable * classTable = NULL;
    err = buildClassTable(root, argv[argc - 1]); // Найти все классы в программе.
    if (err != NULL)
    {
        printf("%s\n", err->errMessage);
        return err->code;
    }

    for(std::map<std::string, std::map<std::string, FunctionTableElement*>>::iterator it = FunctionTable::items.begin(); it != FunctionTable::items.end(); ++it) {
        printf("Function : %s\n", it->first.c_str());
    }

    for(std::map<std::string, ClassTableElement*>::iterator it = ClassTable::items.begin(); it != ClassTable::items.end(); ++it) {
        printf("Class : %s\n", it->first.c_str());
            for(std::map<std::string, std::map<std::string, MethodTableElement*>>::iterator iter = it->second->methods->methods.begin(); iter != it->second->methods->methods.end(); ++iter) {
                printf("\tMethod : %s\n", iter->first.c_str());
                for(std::map<std::string, MethodTableElement*>::iterator iterat = iter->second.begin(); iterat != iter->second.end(); ++iterat) {
                    printf("\t\tDescriptor : %s\n", iterat->first.c_str());
                }
            }
    }

    printf("Classes count : %d\n", ClassTable::items.size());
    printf("Functions count : %d\n", FunctionTable::items.size());


    // Аттрибутировать (проверить) наследование.

    // Вывод дерева после семантического анализа.
    if (needsDotCon || needsDotFile)
    {
        char* res = generateDotFromKotlinFile(root);
        if (needsDotFile)
        {
            FILE* f = fopen("result_sem.gv", "w");
            fprintf(f, "%s", res);
            fclose(f);
        }
        if (needsDotCon)
        {
            printf("%s\n", res);
        }

    }

    // Получить имя класса для свободных функций.
    std::string path = argv[argc - 1];
    size_t sep = path.find_last_of("\\/");
    if (sep != std::string::npos)
        path = path.substr(sep + 1, path.size() - sep - 1);
    sep = path.find_last_of(".");
    if (sep != std::string::npos)
        path[sep + 1] = std::toupper(path[sep + 1]);
    path[0] = std::toupper(path[0]);
    path.erase(sep, 1);

    printf("GENERATION STARTED\n");
    generateClassFile(path);

	return 0;
}

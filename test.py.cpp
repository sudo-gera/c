
/******************************************************************************/
/*defining any*/
#include<any>

/******************************************************************************/
/*defining map*/
#include<map>

/******************************************************************************/
/*defining string*/
#include<string>

/******************************************************************************/
/*defining vector*/
#include<vector>

/******************************************************************************/
/*defining levels*/

				#define python_level_type_first std::u32string
				#define python_level_type_second std::any
				std::vector<std::map<python_level_type_first,python_level_type_second*>> python_globals;
				#define python_global(q)\
				 	if (python_globals[python_globals.size()-1].find(q) == python_globals[python_globals.size()-1].end()){\
						python_locals[q]=0;\
						python_globals[python_globals.size()-1][q]=&(python_locals[q]);\
					}\
					python_globals[python_globals.size()-1][q]=python_globals[0][q];\
					
				#define python_nonlocal(q)\
				 	if (python_globals[python_globals.size()-1].find(q) == python_globals[python_globals.size()-1].end()){\
						python_locals[q]=0;\
						python_globals[python_globals.size()-1][q]=&(python_locals[q]);\
					}\
					python_globals[python_globals.size()-1][q]=python_globals[python_globals.size()-2][q];
					
				#define python_get(q) (*(python_globals[python_globals.size()-1][q]))

				#define python_set(q) python_set_(q,&python_locals)

				python_level_type_second& python_set_(python_level_type_first q,std::map<python_level_type_first,python_level_type_second> *python_locals_pointer){
					if (python_globals[python_globals.size()-1].find(q) == python_globals[python_globals.size()-1].end()){
						(*python_locals_pointer)[q]=0;
						python_globals[python_globals.size()-1][q]=&((*python_locals_pointer)[q]);
					}
					return *(python_globals[python_globals.size()-1][q]);
				}

				#define python_create_level()\
					python_globals.emplace_back();\
					std::map<python_level_type_first,python_level_type_second> python_locals;

				#define python_delete_level()\
					python_globals.pop_back();
			

#define python_headers\
\
/*****************************************************************************/\
/*defining any*/\
\
\
/*****************************************************************************/\
/*defining map*/\
\
\
/*****************************************************************************/\
/*defining string*/\
\
\
/*****************************************************************************/\
/*defining vector*/\
\
\
/*****************************************************************************/\
/*defining levels*/\
\
////////////////////////////////////////////////////////////////////////////////
//main code
	int main(int argc,char **argv){
	python_create_level()
	python_headers
	python_delete_level()}
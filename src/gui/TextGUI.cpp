#include "gui/TextGUI.h"

#include "lib/io.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

CTextGUI *gui=NULL;

//names of menu commands
static const char* N_SET_HMM_AS=		"set_hmm_as";
static const char* N_NEW_HMM=			"new_hmm";
static const char* N_NEW_SVM=			"new_svm";
static const char* N_SET_SVM_TYPE=		"new_svm";
static const char* N_SET_TEST_HMM=		"set_test_HMM";
static const char* N_SET_POS_HMM=		"set_pos_HMM";
static const char* N_SET_NEG_HMM=		"set_neg_HMM";
static const char* N_LOAD_HMM=			"load_HMM";
static const char* N_SAVE_HMM=			"save_HMM";
static const char* N_SAVE_HMM_BIN=		"save_HMM_bin";
static const char* N_LOAD_DEFINITIONS=		"load_defs";
static const char* N_SAVE_KERNEL=		"save_kernel";
static const char* N_SAVE_TOP_FEATURES=		"save_top_features";
#ifndef NOVIT
static const char* N_SAVE_PATH=			"save_path";
static const char* N_SAVE_PATH_DERIVATIVES=	"save_vit_deriv";
static const char* N_SAVE_PATH_DERIVATIVES_BIN=	"save_vit_deriv_bin";
static const char* N_BEST_PATH=			"best_path";
static const char* N_OUTPUT_PATH=      		"output_path";
static const char* N_OUTPUT_GENES=	        "output_genes";
static const char* N_VITERBI_TRAIN=	       	"vit";
static const char* N_VITERBI_TRAIN_DEFINED=     "vit_def";
static const char* N_VITERBI_TRAIN_DEFINED_ANNEALED=    "vit_def_ann";
static const char* N_VITERBI_TRAIN_DEFINED_ADDIABATIC=  "vit_def_add";
#endif // NOVIT
static const char* N_LINEAR_TRAIN=       	"linear_train";
static const char* N_LINEAR_LIKELIHOOD=		"linear_likelihood";
static const char* N_SAVE_LINEAR_LIKELIHOOD=   	"save_linear_likelihood";
static const char* N_SAVE_LINEAR_LIKELIHOOD_BIN="save_linear_likelihood_bin";
static const char* N_SAVE_HMM_DERIVATIVES=      "save_bw_deriv";
static const char* N_SAVE_HMM_DERIVATIVES_BIN=  "save_bw_deriv_bin";
static const char* N_SAVE_LIKELIHOOD=           "save_likelihood";
static const char* N_SAVE_LIKELIHOOD_BIN=       "save_likelihood_bin";
static const char* N_LOAD_OBSERVATIONS=		"load_obs";
static const char* N_ASSIGN_OBSERVATION=	"assign_obs";
static const char* N_CLEAR=			"clear";
static const char* N_CHOP=			"chop";
static const char* N_CONVERGENCE_CRITERIA=	"convergence_criteria";
static const char* N_PSEUDO=			"pseudo";
static const char* N_C=			     	"c";
static const char* N_ADD_STATES=	        "add_states";
static const char* N_APPEND_HMM=		"append_HMM";
static const char* N_BAUM_WELCH_TRAIN=	        "bw";
static const char* N_BAUM_WELCH_TRAIN_DEFINED=	"bw_def";
static const char* N_LIKELIHOOD=	       	"likelihood";
static const char* N_ALPHABET=			"alphabet";
static const char* N_OUTPUT_HMM=		"output_HMM";
static const char* N_OUTPUT_HMM_DEFINED=        "output_HMM_defined";
static const char* N_QUIT=			"quit";
static const char* N_EXEC=			"exec";
static const char* N_EXIT=			"exit";
static const char* N_HELP=			"help";
static const char* N_SYSTEM=			"!";
static const char N_COMMENT1=			'#';
static const char N_COMMENT2=			'%';
static const char* N_FIX_POS_STATE=		"fix_pos_state";
static const char* N_SET_MAX_DIM=		"max_dim";
static const char* N_TEST=			"test";
static const char* N_LINEAR_SVM_TRAIN=		"linear_svm_train";
static const char* N_SVM_TRAIN=			"svm_train";
static const char* N_SVM_TEST=			"svm_test";
static const char* N_SET_SVM_LIGHT=		"set_svm_light";
static const char* N_SET_SVM_CPLEX=		"set_svm_cplex";
static const char* N_SET_SVM_MPI=		"set_svm_mpi";
static const char* N_ONE_CLASS_HMM_TEST=	"one_class_hmm_test";
static const char* N_ONE_CLASS_LINEAR_HMM_TEST=	"one_class_linear_hmm_test";
static const char* N_HMM_TEST=			"hmm_test";
static const char* N_LINEAR_HMM_TEST=		"linear_hmm_test";
static const char* N_SET_ORDER=			"set_order";


CTextGUI::CTextGUI(int argc, const char** argv)
  : CGUI(argc, argv)
{
  CIO::message("Learning uses %i threads\n", NUM_PARALLEL) ;
  
#ifdef SVMCPLEX
  libmmfileInitialize() ;
#endif
}

CTextGUI::~CTextGUI()
{
#ifdef SVMCPLEX
  libmmfileTerminate() ;
#endif
}

void CTextGUI::print_help()
{
   CIO::message("\n[LOAD]\n");
   CIO::message("\033[1;31m%s\033[0m <filename>\t- load hmm\n",N_LOAD_HMM);
   CIO::message("\033[1;31m%s\033[0m <filename> [initialize=1]\t- load hmm defs\n",N_LOAD_DEFINITIONS);
   CIO::message("\033[1;31m%s\033[0m <filename>\t- load observed data\n",N_LOAD_OBSERVATIONS);
   CIO::message("\n[SAVE]\n");
   CIO::message("\033[1;31m%s\033[0m <filename>\t- save hmm\n",N_SAVE_HMM);
   CIO::message("\033[1;31m%s\033[0m <filename>\t- save hmm in binary format\n",N_SAVE_HMM_BIN);
#ifndef NOVIT
   CIO::message("\033[1;31m%s\033[0m <filename>\t- save state sequence of viterbi path\n",N_SAVE_PATH);
   CIO::message("\033[1;31m%s\033[0m <filename>\t- save derivatives of log P[O,Q_best|HMM]\n",N_SAVE_PATH_DERIVATIVES);
   CIO::message("\033[1;31m%s\033[0m <filename>\t- save derivatives of log P[O,Q_best|HMM] in binary format\n",N_SAVE_PATH_DERIVATIVES_BIN);
#endif // NOVIT
   CIO::message("\033[1;31m%s\033[0m <filename>\t- save log derivatives of P[O|HMM]\n",N_SAVE_HMM_DERIVATIVES);
   CIO::message("\033[1;31m%s\033[0m <filename>\t- save log derivatives of P[O|HMM] in binary format\n",N_SAVE_HMM_DERIVATIVES_BIN);
   CIO::message("\033[1;31m%s\033[0m <filename> <TOP|FK>\t- save kernel in binary format\n",N_SAVE_KERNEL);
   CIO::message("\033[1;31m%s\033[0m <filename>\t- save top features for all train obs,neg first\n",N_SAVE_TOP_FEATURES);
   CIO::message("\033[1;31m%s\033[0m <filename>\t- save P[O|HMM]\n",N_SAVE_LIKELIHOOD);
   CIO::message("\033[1;31m%s\033[0m <filename>\t- save P[O|HMM]\n",N_SAVE_LIKELIHOOD_BIN);
   CIO::message("\033[1;31m%s\033[0m <srcname> <destname> [<width> <upto>]\t\t- saves likelihood for linear HMM from file\n",N_SAVE_LINEAR_LIKELIHOOD);
   CIO::message("\033[1;31m%s\033[0m <srcname> <destname> [<width> <upto>]\t\t- saves likelihood for linear HMM from file\n",N_SAVE_LINEAR_LIKELIHOOD_BIN);
   CIO::message("\n[HMM]\n");
   CIO::message("\033[1;31m%s\033[0m - frees all HMMs and observations\n",N_CLEAR);
   CIO::message("\033[1;31m%s\033[0m #states #oberservations #order\t- frees previous HMM and creates an empty new one\n",N_NEW_HMM);
   CIO::message("\033[1;31m%s\033[0m\t- frees previous HMM and creates an empty new one\n",N_NEW_SVM);
   CIO::message("\033[1;31m%s\033[0m <POSTRAIN|NEGTRAIN|POSTEST|NEGTEST|TEST> - assign observation to current HMM\n",N_ASSIGN_OBSERVATION);
   CIO::message("\033[1;31m%s\033[0m - make current HMM the test HMM; then free current HMM \n",N_SET_TEST_HMM);
   CIO::message("\033[1;31m%s\033[0m - make current HMM the positive HMM; then free current HMM \n",N_SET_POS_HMM);
   CIO::message("\033[1;31m%s\033[0m - make current HMM the negative HMM; then free current HMM \n",N_SET_NEG_HMM);
   CIO::message("\033[1;31m%s\033[0m <value>\t\t\t- chops likelihood of all parameters 0<value<1\n", N_CHOP);
   CIO::message("\033[1;31m%s\033[0m <<num> [<value>]>\t\t\t- add num (def 1) states,initialize with value (def rnd)\n", N_ADD_STATES);
   CIO::message("\033[1;31m%s\033[0m <filename> <[ACGT][ACGT]>\t\t\t- append HMM <filename> to current HMM\n", N_APPEND_HMM);
   CIO::message("\033[1;31m%s\033[0m [pseudovalue]\t\t\t- changes pseudo value\n", N_PSEUDO);
   CIO::message("\033[1;31m%s\033[0m <POSTRAIN|NEGTRAIN|POSTEST|NEGTEST|TEST> [PROTEIN|DNA|ALPHANUM|CUBE]\t\t\t- changes alphabet type\n", N_ALPHABET);
   CIO::message("\033[1;31m%s\033[0m [maxiterations] [maxallowedchange]\t- defines the convergence criteria for all train algorithms\n",N_CONVERGENCE_CRITERIA);
#ifdef FIX_POS
   CIO::message("\033[1;31m%s\033[0m position state\t- sets the state which has to be passed at a certain position\n",N_FIX_POS_STATE);
#endif
   CIO::message("\033[1;31m%s\033[0m <max_dim>\t - set maximum number of patterns\n",N_SET_MAX_DIM);
   CIO::message("\033[1;31m%s\033[0m <ORDER>\t - set order of linear HMMs\n",N_SET_ORDER);
   CIO::message("\n[TRAIN]\n");
   CIO::message("\033[1;31m%s\033[0m <filename> [<width> <upto>]\t\t- obtains new linear HMM from file\n",N_LINEAR_TRAIN);
   CIO::message("\033[1;31m%s\033[0m <filename> [<width> <upto>]\t\t- computes likelihood for linear HMM from file\n",N_LINEAR_LIKELIHOOD);
#ifndef NOVIT
   CIO::message("\033[1;31m%s\033[0m\t\t- does viterbi training on the current HMM\n",N_VITERBI_TRAIN);
   CIO::message("\033[1;31m%s\033[0m\t\t- does viterbi training only on defined transitions etc\n",N_VITERBI_TRAIN_DEFINED);
   CIO::message("\033[1;31m%s\033[0m [pseudo_start [in_steps]]\t\t- does viterbi training only on defined transitions with annealing\n",N_VITERBI_TRAIN_DEFINED_ANNEALED);
   CIO::message("\033[1;31m%s\033[0m [pseudo_start [step [eps_add]]]\t\t- does viterbi training only on defined transitions with addiabatic annealing\n",N_VITERBI_TRAIN_DEFINED_ADDIABATIC);
#endif //NOVIT
   CIO::message("\033[1;31m%s\033[0m\t\t- does baum welch training on current HMM\n",N_BAUM_WELCH_TRAIN);
   CIO::message("\033[1;31m%s\033[0m\t\t- does baum welch training only on defined transitions etc.\n",N_BAUM_WELCH_TRAIN_DEFINED);
#ifndef NOVIT
   CIO::message("\033[1;31m%s\033[0m\t- find the best path using viterbi\n",N_BEST_PATH);
#endif //NOVIT
   CIO::message("\033[1;31m%s\033[0m\t- find HMM likelihood\n",N_LIKELIHOOD);
   CIO::message("\033[1;31m%s\033[0m [maxiterations] [maxallowedchange]\t- defines the convergence criteria for all train algorithms\n",N_CONVERGENCE_CRITERIA);
   CIO::message("\n[OUTPUT]\n");
#ifndef NOVIT
   CIO::message("\033[1;31m%s\033[0m [from to]\t- outputs best path\n",N_OUTPUT_PATH);
#endif //NOVIT
   CIO::message("\033[1;31m%s\033[0m\t- output whole HMM\n",N_OUTPUT_HMM);
   CIO::message("\n[HMM-classification]\n");
   CIO::message("\033[1;31m%s\033[0m[<treshhold> [<output> [<rocfile>]]]\t\t\t\t- calculate output from obs using test HMM\n",N_ONE_CLASS_HMM_TEST);
   CIO::message("\033[1;31m%s\033[0m[<output> [<rocfile>]]\t\t\t\t- calculate output from obs using current HMMs\n",N_HMM_TEST);
   CIO::message("\033[1;31m%s\033[0m <negtest> <postest> [<treshhold> [<output> [<rocfile>]]]\t\t\t\t- calculate output from obs using test HMM\n",N_ONE_CLASS_LINEAR_HMM_TEST);
   CIO::message("\033[1;31m%s\033[0m <negtest> <postest> [<output> [<rocfile> [<width> <upto>]]]\t- calculate hmm output from obs using linear HMM\n",N_LINEAR_HMM_TEST);
   CIO::message("\n[Hybrid HMM-<TOP-Kernel>-SVM]\n");
   CIO::message("\033[1;31m%s\033[0m [c-value]\t\t\t- changes svm_c value\n", N_C);
   CIO::message("\033[1;31m%s\033[0m <dstsvm>\t\t- obtains svm from POS/NEGTRAIN using pos/neg HMM\n",N_SVM_TRAIN);
   CIO::message("\033[1;31m%s\033[0m <srcsvm> [<output> [<rocfile>]]\t\t- calculate [linear_]svm output from obs using current HMM\n",N_SVM_TEST);
   CIO::message("\033[1;31m%s\033[0m <dstsvm> \t\t- obtains svm from pos/neg linear HMMs\n",N_LINEAR_SVM_TRAIN);
   CIO::message("\033[1;31m%s\033[0m - enables SVM Light \n",N_SET_SVM_LIGHT);
#ifdef SVMCPLEX
   CIO::message("\033[1;31m%s\033[0m - enables SVM CPLEX \n",N_SET_SVM_CPLEX);
#endif
   CIO::message("\n[SYSTEM]\n");
   CIO::message("\033[1;31m%s\033[0m <filename>\t- load and execute a script\n",N_EXEC);
   CIO::message("\033[1;31m%s\033[0m\t- exit genfinder\n",N_QUIT);
   CIO::message("\033[1;31m%s\033[0m\t- exit genfinder\n",N_EXIT);
   CIO::message("\033[1;31m%s\033[0m\t- this message\n",N_HELP);
   CIO::message("\033[1;31m%s\033[0m <commands>\t- execute system functions \n",N_SYSTEM);
   
}

void CTextGUI::print_prompt()
{
  cout << flush ;
  cerr << flush ;
  CIO::message(stderr,"\033[1;34mgenefinder\033[0m >> ");
  cout << flush ;
  cerr << flush ;
    //CIO::message("genefinder >> ");
}

bool CTextGUI::get_line(FILE* infile)
{
	int i;
	char input[2000];

	print_prompt();

	char* b=fgets(input, sizeof(input), infile);
	if ((b==NULL) || !strlen(input) || (input[0]==N_COMMENT1) || (input[0]==N_COMMENT2) || (input[0]=='\n'))
		return true;

	input[strlen(input)-1]='\0';
	if (infile!=stdin)
		printf("%s\n",input) ;
	
	if (!strncmp(input, N_NEW_HMM, strlen(N_NEW_HMM)))
	{
		guihmm.new_hmm(input+strlen(N_NEW_HMM));
	} 
	else if (!strncmp(input, N_NEW_SVM, strlen(N_NEW_SVM)))
	{
		guisvm.new_svm(input+strlen(N_NEW_SVM));
	} 
	else if (!strncmp(input, N_LOAD_HMM, strlen(N_LOAD_HMM)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_SET_HMM_AS, strlen(N_SET_HMM_AS)))
	{
		guihmm.set_hmm_as(input+strlen(N_SET_HMM_AS));
	}
	else if (!strncmp(input, N_SAVE_HMM_BIN, strlen(N_SAVE_HMM_BIN)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_CHOP, strlen(N_CHOP)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_SAVE_HMM, strlen(N_SAVE_HMM)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_LOAD_DEFINITIONS, strlen(N_LOAD_DEFINITIONS)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_ASSIGN_OBSERVATION, strlen(N_ASSIGN_OBSERVATION)))
	{
	  guihmm.assign_obs(input+strlen(N_ASSIGN_OBSERVATION)) ;
	}
	else if (!strncmp(input, N_LOAD_OBSERVATIONS, strlen(N_LOAD_OBSERVATIONS)))
	{
	  guiobs.load_observations(input+strlen(N_LOAD_OBSERVATIONS));
	}
	else if (!strncmp(input, N_SAVE_PATH, strlen(N_SAVE_PATH)))
	{
	  CIO::not_implemented() ;
	}
	else if (!strncmp(input, N_SAVE_LIKELIHOOD_BIN, strlen(N_SAVE_LIKELIHOOD_BIN)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_SAVE_LIKELIHOOD, strlen(N_SAVE_LIKELIHOOD)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_SAVE_TOP_FEATURES, strlen(N_SAVE_TOP_FEATURES)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_SAVE_KERNEL, strlen(N_SAVE_KERNEL)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_SAVE_PATH_DERIVATIVES_BIN, strlen(N_SAVE_PATH_DERIVATIVES_BIN)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_SAVE_PATH_DERIVATIVES, strlen(N_SAVE_PATH_DERIVATIVES)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_SAVE_HMM_DERIVATIVES_BIN, strlen(N_SAVE_HMM_DERIVATIVES_BIN)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_SAVE_HMM_DERIVATIVES, strlen(N_SAVE_HMM_DERIVATIVES)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_FIX_POS_STATE, strlen(N_FIX_POS_STATE)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_SET_MAX_DIM, strlen(N_SET_MAX_DIM)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_CLEAR, strlen(N_CLEAR)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_PSEUDO, strlen(N_PSEUDO)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_ALPHABET, strlen(N_ALPHABET)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_CONVERGENCE_CRITERIA, strlen(N_CONVERGENCE_CRITERIA)))
	{
	  guihmm.convergence_criteria(input+strlen(N_CONVERGENCE_CRITERIA)) ;
	} 
	else if (!strncmp(input, N_VITERBI_TRAIN_DEFINED_ANNEALED, strlen(N_VITERBI_TRAIN_DEFINED_ANNEALED)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_VITERBI_TRAIN_DEFINED_ADDIABATIC, strlen(N_VITERBI_TRAIN_DEFINED_ADDIABATIC)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_VITERBI_TRAIN_DEFINED, strlen(N_VITERBI_TRAIN_DEFINED)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_VITERBI_TRAIN, strlen(N_VITERBI_TRAIN)))
	{
	  CIO::not_implemented() ;
	}
	else if (!strncmp(input, N_BAUM_WELCH_TRAIN_DEFINED, strlen(N_BAUM_WELCH_TRAIN_DEFINED)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_BAUM_WELCH_TRAIN, strlen(N_BAUM_WELCH_TRAIN)))
	{
		guihmm.baum_welch_train(input+strlen(N_BAUM_WELCH_TRAIN));
	} 
	else if (!strncmp(input, N_BEST_PATH, strlen(N_BEST_PATH)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_LIKELIHOOD, strlen(N_LIKELIHOOD)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_OUTPUT_HMM_DEFINED, strlen(N_OUTPUT_HMM_DEFINED)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_OUTPUT_PATH, strlen(N_OUTPUT_PATH)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_OUTPUT_GENES, strlen(N_OUTPUT_GENES)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_OUTPUT_HMM, strlen(N_OUTPUT_HMM)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_EXEC, strlen(N_EXEC)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_EXIT, strlen(N_EXIT)))
	{
		return false;
	} 
	else if (!strncmp(input, N_QUIT, strlen(N_QUIT)))
	{
		return false;
	} 
	else if (!strncmp(input, N_TEST, strlen(N_TEST)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_HELP, strlen(N_HELP)))
	{
		print_help();
	}
	else if (!strncmp(input, N_SYSTEM, strlen(N_SYSTEM)))
	{
		for (i=strlen(N_SYSTEM); isspace(input[i]); i++);
		system(&input[i]);
	} 
	else if (!strncmp(input, N_LINEAR_TRAIN, strlen(N_LINEAR_TRAIN)))
	{
		guihmm.linear_train(input+strlen(N_LINEAR_TRAIN));
	} 
	else if (!strncmp(input, N_LINEAR_LIKELIHOOD, strlen(N_LINEAR_LIKELIHOOD)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_SAVE_LINEAR_LIKELIHOOD_BIN, strlen(N_SAVE_LINEAR_LIKELIHOOD_BIN)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_SAVE_LINEAR_LIKELIHOOD, strlen(N_SAVE_LINEAR_LIKELIHOOD)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_SVM_TRAIN, strlen(N_SVM_TRAIN)))
	{
		guisvm.train(input+strlen(N_SVM_TRAIN));
	} 
	else if (!strncmp(input, N_SET_SVM_TYPE, strlen(N_SET_SVM_TYPE)))
	{
		guisvm.set_svm_type(input+strlen(N_SET_SVM_TYPE));
	}
	else if (!strncmp(input, N_LINEAR_SVM_TRAIN, strlen(N_LINEAR_SVM_TRAIN)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_SVM_TEST, strlen(N_SVM_TEST)))
	{
		guisvm.test(input+strlen(N_SVM_TEST));
	} 
	else if (!strncmp(input, N_ONE_CLASS_LINEAR_HMM_TEST, strlen(N_ONE_CLASS_LINEAR_HMM_TEST)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_LINEAR_HMM_TEST, strlen(N_LINEAR_HMM_TEST)))
	{
	  CIO::not_implemented() ;
	} 
	else if (!strncmp(input, N_ONE_CLASS_HMM_TEST, strlen(N_ONE_CLASS_HMM_TEST)))
	{
		guihmm.one_class_test(input+strlen(N_ONE_CLASS_HMM_TEST));
	} 
	else if (!strncmp(input, N_HMM_TEST, strlen(N_HMM_TEST)))
	{
		guihmm.test_hmm(input+strlen(N_HMM_TEST));
	} 
	else if (!strncmp(input, N_APPEND_HMM, strlen(N_APPEND_HMM)))
	{
		guihmm.append_model(input+strlen(N_APPEND_HMM));
	} 
	else if (!strncmp(input, N_ADD_STATES, strlen(N_ADD_STATES)))
	{
		guihmm.add_states(input+strlen(N_ADD_STATES));
	} 
	else if (!strncmp(input, N_C, strlen(N_C)))
	{
		guisvm.set_C(input+strlen(N_C));
	} 
	else if (!strncmp(input, N_SET_ORDER, strlen(N_SET_ORDER)))
	{
	  CIO::not_implemented() ;
	}
	else
		CIO::message("unrecognized command. type help for options\n");
	return true;
}

//// main - the one and only ///
int main(int argc, const char* argv[])
{
  gui=new CTextGUI(argc, argv) ;

  if (argc<=1)
    while (gui->get_line());
  else
    {
      if (argc>=2)
	{
	  if ( argc>2 || !strcmp(argv[1], "-h") || !strcmp(argv[1], "/?") || !strcmp(argv[1], "--help"))
	    {
	      printf("usage: genfinder [ <script> ]\n\n");
	      printf("if no options are given genfinder enters interactive mode\n");
	      printf("if <script> is specified the commands will be executed");
	      return 1;
	    }
	  else
	    {
	      FILE* file=fopen(argv[1], "r");
	      
	      if (!file)
		{
		  CIO::message("error opening/reading file: \"%s\"",argv[1]);
		  return 1;
		}
	      else
		{
		  while(!feof(file) && gui->get_line(file));
		  fclose(file);
		}
	    }
	}
    }
  return 0;
}

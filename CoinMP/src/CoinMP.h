/************************************************************************/
/*                                                                      */
/*  COINMP.DLL                                        Maximal Software  */
/*                                                                      */
/*  File         :  'coinmp.h'                                          */
/*                                                                      */
/*  Version      :  1.2                                                 */
/*                                                                      */
/*  Author       :  Bjarni Kristjansson, Maximal Software               */
/*                                                                      */
/*  Copyright (c) 2002-2008                     Bjarni Kristjansson     */
/*                                                                      */
/************************************************************************/


#ifndef _COINMP_H_
#define _COINMP_H_


#if defined(_MSC_VER)
#ifdef SOLVER_EXPORT
#define SOLVAPI extern "C"  __declspec(dllexport)  
#define SOLVFUNC   
#else
#define SOLVAPI __declspec(dllimport)
#define SOLVFUNC 
#endif
#else
#define SOLVAPI
#define SOLVFUNC
#endif


#ifndef SOLV_LINK_LIB
#ifndef SOLV_LINK_DLL
#define SOLV_LINK_LIB
#endif
#endif



#define SOLV_CALL_SUCCESS   1
#define SOLV_CALL_FAILED    0

#define SOLV_METHOD_DEFAULT       0x00000000L

#define SOLV_METHOD_PRIMAL        0x00000001L
#define SOLV_METHOD_DUAL          0x00000002L
#define SOLV_METHOD_NETWORK       0x00000004L
#define SOLV_METHOD_BARRIER       0x00000008L

#define SOLV_METHOD_BENDERS       0x00000100L
#define SOLV_METHOD_DEQ           0x00000200L
#define SOLV_METHOD_EV            0x00000400L


#define SOLV_FEATURE_LP            0x00000001L
#define SOLV_FEATURE_QP            0x00000002L
#define SOLV_FEATURE_QCP           0x00000004L
#define SOLV_FEATURE_NLP           0x00000008L

#define SOLV_FEATURE_MIP           0x00000010L
#define SOLV_FEATURE_MIQP          0x00000020L
#define SOLV_FEATURE_MIQCP         0x00000040L
#define SOLV_FEATURE_MINLP         0x00000080L

#define SOLV_FEATURE_SP            0x00010000L


#define SOLV_OBJSENS_MAX   -1
#define SOLV_OBJSENS_MIN    1


#define SOLV_FILE_LOG      0
#define SOLV_FILE_BASIS    1
#define SOLV_FILE_MIPSTART 2
#define SOLV_FILE_MPS      3
#define SOLV_FILE_LP       4
#define SOLV_FILE_BINARY   5
#define SOLV_FILE_OUTPUT   6
#define SOLV_FILE_BINOUT   7
#define SOLV_FILE_IIS      8



typedef void *HPROB;

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*MSGLOGCALLBACK)(char *MessageStr);

typedef int (*ITERCALLBACK)(int    IterCount, 
							double ObjectValue,
							int    IsFeasible, 
							double InfeasValue);

typedef int (*MIPNODECALLBACK)(int    IterCount, 
							   int	  MipNodeCount,
							   double BestBound,
							   double BestInteger,
							   int    IsMipImproved);



#ifdef SOLV_LINK_LIB

SOLVAPI int    CoinInitSolver(char *LicenseStr);
SOLVAPI int    CoinFreeSolver(void);

SOLVAPI char*  CoinGetSolverName(void);
SOLVAPI char*  CoinGetVersionStr(void);
SOLVAPI double CoinGetVersion(void);
SOLVAPI int    CoinGetFeatures(void);
SOLVAPI int    CoinGetMethods(void);
SOLVAPI double CoinGetInfinity(void);

SOLVAPI HPROB  CoinCreateProblem(char *ProblemName);

SOLVAPI int    CoinLoadProblem(HPROB hProb, 
							   int ColCount, int RowCount, int NonZeroCount, int RangeCount, 
							   int ObjectSense, double* ObjectCoeffs, double ObjectConst,
							   double* RHSValues,  double* RangeValues, char* RowType, 
							   int* MatrixBegin, int* MatrixCount,   int* MatrixIndex,    
							   double* MatrixValues, double* LowerBounds, double* UpperBounds, 
							   double* InitValues, char** ColNames, char** RowNames);

SOLVAPI int    CoinLoadInteger(HPROB hProb, char* ColumnType);


SOLVAPI int    CoinLoadPriority(HPROB hProb, int PriorCount, int *PriorIndex, 
										  int *PriorValues, int *BranchDir);

SOLVAPI int    CoinLoadSos(HPROB hProb, int SosCount, int SosNZCount, 
						   char *SosType, int *SosPrior, int *SosBegin,   
						   int *SosIndex, double *SosRef);

SOLVAPI int    CoinLoadQuadratic(HPROB hProb, int *QuadBegin, int *QuadCount, 
								 int *QuadIndex, double *QuadValues);

SOLVAPI int    CoinLoadNonlinear(HPROB hProb, int NlpTreeCount, int NlpLineCount, 
								 int *NlpBegin, int *NlpOper, int *NlpArg1, 
								 int *NlpArg2, int *NlpIndex1, int *NlpIndex2, 
								 double *NlpValue1, double *NlpValue2);

SOLVAPI int    CoinUnloadProblem(HPROB hProb);

SOLVAPI int    CoinSetMsgLogCallback(HPROB hProb, MSGLOGCALLBACK MsgLogCallback);
SOLVAPI int    CoinSetIterCallback(HPROB hProb, ITERCALLBACK IterCallback);
SOLVAPI int    CoinSetMipNodeCallback(HPROB hProb, MIPNODECALLBACK MipNodeCallback);

SOLVAPI int    CoinOptimizeProblem(HPROB hProb, int Method);

SOLVAPI int    CoinGetSolutionStatus(HPROB hProb);
SOLVAPI char*  CoinGetSolutionText(HPROB hProb, int SolutionStatus);
SOLVAPI double CoinGetObjectValue(HPROB hProb);
SOLVAPI double CoinGetMipBestBound(HPROB hProb);

SOLVAPI int    CoinGetIterCount(HPROB hProb);
SOLVAPI int    CoinGetMipNodeCount(HPROB hProb);

SOLVAPI int    CoinGetSolutionValues(HPROB hProb, double* Activity, double* ReducedCost, 
									 double* SlackValues, double* ShadowPrice);
SOLVAPI int    CoinGetSolutionRanges(HPROB hProb, double *ObjLoRange, double *ObjUpRange,
									 double *RhsLoRange, double *RhsUpRange);
SOLVAPI int    CoinGetSolutionBasis(HPROB hProb, int *ColStatus, double *RowStatus);

SOLVAPI int    CoinReadFile(HPROB hProb, int FileType, char *ReadFilename);
SOLVAPI int    CoinWriteFile(HPROB hProb, int FileType, char *WriteFilename);

SOLVAPI int    CoinOpenLogFile(HPROB hProb, char *LogFilename);
SOLVAPI int    CoinCloseLogFile(HPROB hProb);

SOLVAPI int    CoinGetOptionCount(HPROB hProb);
SOLVAPI int    CoinGetOptionInfo(HPROB hProb, int OptionNr, int *OptionID, int *GroupType,
								 int *OptionType, char *OptionName, char *ShortName);

SOLVAPI int    CoinGetIntOptionMinMax(HPROB hProb, int OptionNr, int *MinValue, int *MaxValue);
SOLVAPI int    CoinGetRealOptionMinMax(HPROB hProb, int OptionNr, double *MinValue, double *MaxValue);

SOLVAPI int    CoinGetOptionChanged(HPROB hProb, int OptionID);

SOLVAPI int    CoinGetIntOption(HPROB hProb, int OptionID);
SOLVAPI int    CoinSetIntOption(HPROB hProb, int OptionID, int IntValue);

SOLVAPI double CoinGetRealOption(HPROB hProb, int OptionID);
SOLVAPI int    CoinSetRealOption(HPROB hProb, int OptionID, double RealValue);

SOLVAPI char*  CoinGetStringOption(HPROB hProb, int OptionID);
SOLVAPI int    CoinSetStringOption(HPROB hProb, int OptionID, char *StringValue);


#endif


#ifdef SOLV_LINK_DLL

int    (SOLVFUNC *CoinInitSolver)(char *LicenseStr);
int    (SOLVFUNC *CoinFreeSolver)(void);

char*  (SOLVFUNC *CoinGetSolverName)(void);
char*  (SOLVFUNC *CoinGetVersionStr)(void);
double (SOLVFUNC *CoinGetVersion)(void);
int    (SOLVFUNC *CoinGetFeatures)(void);
int    (SOLVFUNC *CoinGetMethods)(void);
double (SOLVFUNC *CoinGetInfinity)(void);

HPROB  (SOLVFUNC *CoinCreateProblem)(char *ProblemName);

int    (SOLVFUNC *CoinLoadProblem)(HPROB hProb, 
								   int ColCount, int RowCount, int NonZeroCount, int RangeCount, 
								   int ObjectSense, double* ObjectCoeffs, double ObjectConst,
								   double* RHSValues, double* RangeValues, char* RowType, 
								   int* MatrixBegin, int* MatrixCount, int* MatrixIndex,    
								   double* MatrixValues, double* LowerBounds, double* UpperBounds, 
								   double* InitValues, char** ColNames, char** RowNames);

int    (SOLVFUNC *CoinLoadInteger)(HPROB hProb, char* ColumnType);

int    (SOLVFUNC *CoinLoadPriority)(HPROB hProb, int PriorCount, int *PriorIndex, 
												int *PriorValues, int *BranchDir);

int    (SOLVFUNC *CoinLoadSos)(HPROB hProb, int SosCount, int SosNZCount, 
										 char *SosType, int *SosPrior, int *SosBegin,   
										 int *SosIndex, double *SosRef);

int    (SOLVFUNC *CoinLoadQuadratic)(HPROB hProb, int *QuadBegin, int *QuadCount, 
												 int *QuadIndex, double *QuadValues);

int    (SOLVFUNC *CoinLoadNonlinear)(HPROB hProb, int NlpTreeCount, int NlpLineCount, 
												 int *NlpBegin, int *NlpOper, int *NlpArg1, 
												 int *NlpArg2, int *NlpIndex1, int *NlpIndex2, 
												 double *NlpValue1, double *NlpValue2);

int    (SOLVFUNC *CoinUnloadProblem)(HPROB hProb);

void   (SOLVFUNC *CoinSetMsgLogCallback)(HPROB hProb, MSGLOGCALLBACK MsgLogCallback);
void   (SOLVFUNC *CoinSetIterCallback)(HPROB hProb, ITERCALLBACK IterCallback);
void   (SOLVFUNC *CoinSetMipNodeCallback)(HPROB hProb, MIPNODECALLBACK MipNodeCallback);

int    (SOLVFUNC *CoinOptimizeProblem)(HPROB hProb, int Method);

int    (SOLVFUNC *CoinGetSolutionStatus)(HPROB hProb);
char*  (SOLVFUNC *CoinGetSolutionText)(HPROB hProb, int SolutionStatus);
double (SOLVFUNC *CoinGetObjectValue)(HPROB hProb);
double (SOLVFUNC *CoinGetMipBestBound)(HPROB hProb);

int    (SOLVFUNC *CoinGetIterCount)(HPROB hProb);
int    (SOLVFUNC *CoinGetMipNodeCount)(HPROB hProb);

int    (SOLVFUNC *CoinGetSolutionValues)(HPROB hProb, double* Activity, double* ReducedCost, 
													  double* SlackValues, double* ShadowPrice);
int    (SOLVFUNC *CoinGetSolutionRanges)(HPROB hProb, double *ObjLoRange, double *ObjUpRange,
										           double *RhsLoRange, double *RhsUpRange);
int    (SOLVFUNC *CoinGetSolutionBasis)(HPROB hProb, int *ColStatus, double *RowStatus);

void   (SOLVFUNC *CoinReadFile)(HPROB hProb, int FileType, char* ReadFilename);
void   (SOLVFUNC *CoinWriteFile)(HPROB hProb, int FileType, char* WriteFilename);

void   (SOLVFUNC *CoinOpenLogFile)(HPROB hProb, char *LogFilename);
void   (SOLVFUNC *CoinCloseLogFile)(HPROB hProb);

int    (SOLVFUNC *CoinGetOptionCount)(HPROB hProb);
int    (SOLVFUNC *CoinGetOptionInfo)(HPROB hProb, int OptionNr, int *OptionID, 
									int *OptionType, char *OptionName, char *ShortName);

int    (SOLVFUNC *CoinGetIntOptionMinMax)(HPROB hProb, int OptionNr, int *MinValue, int *MaxValue);
int    (SOLVFUNC *CoinGetRealOptionMinMax)(HPROB hProb, int OptionNr, double *MinValue, double *MaxValue);

int    (SOLVFUNC *CoinGetOptionChanged)(HPROB hProb, int OptionID);

int    (SOLVFUNC *CoinGetIntOption)(HPROB hProb, int OptionID);
int    (SOLVFUNC *CoinSetIntOption)(HPROB hProb, int OptionID, int IntValue);

double (SOLVFUNC *CoinGetRealOption)(HPROB hProb, int OptionID);
int    (SOLVFUNC *CoinSetRealOption)(HPROB hProb, int OptionID, double RealValue);

char*  (SOLVFUNC *CoinGetStringOption)(HPROB hProb, int OptionID);
int    (SOLVFUNC *CoinSetStringOption)(HPROB hProb, int OptionID, char *StringValue);

#endif

#ifdef __cplusplus
}
#endif



#define COIN_INT_SOLVEMETHOD     1
#define COIN_INT_PRESOLVETYPE    2
#define COIN_INT_SCALING         3
#define COIN_INT_PERTURBATION    4
#define COIN_INT_PRIMALPIVOTALG  5
#define COIN_INT_DUALPIVOTALG    6
#define COIN_INT_LOGLEVEL        7
#define COIN_INT_MAXITER         8
#define COIN_INT_CRASHIND        9     
#define COIN_INT_CRASHPIVOT     10
#define COIN_REAL_CRASHGAP      11
#define COIN_REAL_PRIMALOBJLIM  12
#define COIN_REAL_DUALOBJLIM    13
#define COIN_REAL_PRIMALOBJTOL  14
#define COIN_REAL_DUALOBJTOL    15
#define COIN_REAL_MAXSECONDS    16

#define COIN_INT_MIPMAXNODES    17
#define COIN_INT_MIPMAXSOL      18
#define COIN_REAL_MIPMAXSEC     19

#define COIN_INT_MIPFATHOMDISC     20
#define COIN_INT_MIPHOTSTART       21
//#define COIN_INT_MIPFORCEPRIOR     21
#define COIN_INT_MIPMINIMUMDROP    22
#define COIN_INT_MIPMAXCUTPASS     23
#define COIN_INT_MIPMAXPASSROOT    24
#define COIN_INT_MIPSTRONGBRANCH   25
#define COIN_INT_MIPSCANGLOBCUTS   26

#define COIN_REAL_MIPINTTOL        30
#define COIN_REAL_MIPINFWEIGHT     31
#define COIN_REAL_MIPCUTOFF        32
#define COIN_REAL_MIPABSGAP        33

#define COIN_INT_MIPCUT_PROBING          110
#define COIN_INT_MIPPROBE_FREQ           111
#define COIN_INT_MIPPROBE_MODE           112
#define COIN_INT_MIPPROBE_USEOBJ         113
#define COIN_INT_MIPPROBE_MAXPASS        114
#define COIN_INT_MIPPROBE_MAXPROBE       115
#define COIN_INT_MIPPROBE_MAXLOOK        116
#define COIN_INT_MIPPROBE_ROWCUTS        117

#define COIN_INT_MIPCUT_GOMORY           120
#define COIN_INT_MIPGOMORY_FREQ          121
#define COIN_INT_MIPGOMORY_LIMIT         122
#define COIN_REAL_MIPGOMORY_AWAY         123


#define COIN_INT_MIPCUT_KNAPSACK         130
#define COIN_INT_MIPKNAPSACK_FREQ        131
#define COIN_INT_MIPKNAPSACK_MAXIN       132

#define COIN_INT_MIPCUT_ODDHOLE          140
#define COIN_INT_MIPODDHOLE_FREQ         141
#define COIN_REAL_MIPODDHOLE_MINVIOL     142
#define COIN_REAL_MIPODDHOLE_MINVIOLPER  143
#define COIN_INT_MIPODDHOLE_MAXENTRIES   144

#define COIN_INT_MIPCUT_CLIQUE           150
#define COIN_INT_MIPCLIQUE_FREQ          151
#define COIN_INT_MIPCLIQUE_PACKING       152
#define COIN_INT_MIPCLIQUE_STAR          153
#define COIN_INT_MIPCLIQUE_STARMETHOD    154
#define COIN_INT_MIPCLIQUE_STARMAXLEN    155
#define COIN_INT_MIPCLIQUE_STARREPORT    156
#define COIN_INT_MIPCLIQUE_ROW           157
#define COIN_INT_MIPCLIQUE_ROWMAXLEN     158
#define COIN_INT_MIPCLIQUE_ROWREPORT     159
#define COIN_REAL_MIPCLIQUE_MINVIOL      160

#define COIN_INT_MIPCUT_LIFTPROJECT      170
#define COIN_INT_MIPLIFTPRO_FREQ         171
#define COIN_INT_MIPLIFTPRO_BETAONE      172

#define COIN_INT_MIPCUT_SIMPROUND        180
#define COIN_INT_MIPSIMPROUND_FREQ       181   

#define COIN_INT_MIPUSECBCMAIN           200   


#endif  /* _COINMP_H_ */

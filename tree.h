struct _NodeProgram* semTree;

typedef struct _NodeIndexList {
	struct _NodeExp *exp;
	struct _NodeIndexList *next;
} NodeIndexList;

typedef enum {
	multiExp,
	addExp,
	minusExp,
	divExp,
	greaterExp,
	lessExp,
	GEExp,
	LEExp,
	notExp,
	andExp,
	orExp,
	constant,
	varExp,
	chamada,
	unMinusExp,
	eqExp
} ExpTag;

typedef struct _NodeExp {
	ExpTag tag;
	union {
		struct {
			struct _NodeExp *l;
			struct _NodeExp *r;
		} binary_exp;
		struct _NodeExp *unary_exp;
		struct _NodeVar *var;
		struct _NodeChamada *chamada;
		struct _NodeConst *k;
	} u;
} NodeExp;

typedef enum {
	vint,
	vchar,
	vstring,
	vfloat
} ConstTag;

typedef struct _NodeConst {
	ConstTag tag;
	union {
		int i;
		float f;
		char c;
		char *s;
	} u;
} NodeConst;


typedef struct _NodeVar {
	char *id;
	struct _NodeIndexList *indexList;
} NodeVar;

typedef enum {
	cif,
	cifelse,
	cwhile,
	cassign,
	creturn,
	cchamada,
	cbloco
} ComandoTag;

typedef struct _NodeComando {
	ComandoTag tag;
	union {
		struct {
			struct _NodeExp *cond;
			struct _NodeComando *command;
		} cif;
		struct {
			struct _NodeExp *cond;
			struct _NodeComando *ifCommand;
			struct _NodeComando *elseCommand;
		} cifelse;
		struct {
			struct _NodeExp *cond;
			struct _NodeComando *command;
		} cwhile;
		struct {
			struct _NodeVar *var;
			struct _NodeExp *exp;
		} cassign;
		struct _NodeExp *returnExp;
		struct _NodeChamada *chamada;
		struct _NodeBloco *bloco;
	} u;
} NodeComando;

// chamada	: ID OpeningParenthesis listaexp ClosingParenthesis

typedef struct _NodeChamada {
	char *id;
	struct _NodeListaExp *parans;
} NodeChamada;

typedef struct _NodeListaExp {
	struct _NodeExp *exp;
	struct _NodeListaExp *list;
} NodeListaExp;

typedef enum {
	dec,
	command
} BlocoTag;

typedef struct _NodeBloco {
	BlocoTag tag;
	struct _NodeBloco *next;
	union {
		struct _NodeDecVar *dec;
		struct _NodeComando *command;
	} u;
} NodeBloco;

typedef struct _NodeDecVar {
	struct _NodeTipo *tipo;
	struct _NodeListaNomes *lista;
} NodeDecVar;

typedef struct _NodeListaNomes {
	char *id;
	struct _NodeListaNomes *next;
} NodeListaNomes;

typedef enum {
	tint,
	tchar,
	tfloat,
	tvoid,
} TipoTag;

typedef struct _NodeTipo {
	TipoTag tag;
	int dimensions;
} NodeTipo;

typedef struct _NodeParam {
	char *id;
	struct _NodeParam* next;
	struct _NodeTipo* tipo;
} NodeParam;

typedef enum {
	func,
	decvar
} DecTag;

typedef struct _NodeDecLista {
	DecTag tag;
	struct _NodeDecLista *next;
	union {
		struct _NodeDecVar *var;
		struct _NodeDecFunc *func;
	} u;
} NodeDecLista;

typedef struct _NodeDecFunc {
	struct NodeTipo *tipo;
	char* id;
	struct _NodeParam *params;
	struct _NodeBloco *bloco;
} NodeDecFunc;

typedef struct _NodeProgram {
	struct _NodeDecLista *listaDec;
} NodeProgram;

typedef enum
{
	i,
	c,
	f,
	s,
	indexList,
	var,
	exp,
	listExp,
	chamada,
	constant,
	command,
	bloco,
	decVar,
	listaNomes,
	tipo,
	param,
	declista,
	decfunc,
	program
} TreeNodeTag;

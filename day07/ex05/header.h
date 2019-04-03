#ifndef HEADER_H
# define HEADER_H

/*--------------------------------
  !! required structure
  --------------------------------*/

struct s_node {
	char		      c;
	unsigned int	isWord:1;
	struct        s_node	**child;
};

struct s_trie {
	struct s_node *node;
};

typedef struct s_trie t_trie;
typedef struct s_node t_node;
/*--------------------------------
  :) function you must implement
  --------------------------------*/
struct s_trie *createTrie(char **dictionary);
char *understand(char *word, struct s_trie *trie);

/*--------------------------------
  :) function you must implement
  --------------------------------*/

char *neverForget(char *words, char **dictionary);


/*--------------------------------
  ?? test function used in main 
  --------------------------------*/

extern char *g_dict[];

char *get_content(char *file);


/*--------------------------------
  &  your own other function
  --------------------------------*/

int recur(char *word, char **buf, t_node *node);

#endif

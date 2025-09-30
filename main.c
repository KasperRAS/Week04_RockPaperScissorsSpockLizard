#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// --- Data types & labels ---
enum Shape { ROCK, PAPER, SCISSORS, SPOCK, LIZARD, SHAPE_COUNT };
static const char *SHAPE_NAME[SHAPE_COUNT] = { "Rock ", "Paper ", "Scissors ", "Spock ", "Lizard " };
static const char *SHAPE_EMOJI[SHAPE_COUNT] = { "🪨", "📄", "✂️", "🖖", "🦎" };

enum Outcome { TIE = 0, HUMAN_WINS = 1, AGENT_WINS = 2 };

// --- Win Condition ---
enum { WINNING_SCORE = 5 };

// --- Resolution table (Rows: Human, Columns: Agent) ---
static const enum Outcome RES[SHAPE_COUNT][SHAPE_COUNT] = {
  /*            R           P           S           Sp          L       */
  /* R  */   { TIE,        AGENT_WINS, HUMAN_WINS, AGENT_WINS, HUMAN_WINS },
  /* P  */   { HUMAN_WINS, TIE,        AGENT_WINS, HUMAN_WINS, AGENT_WINS },
  /* S  */   { AGENT_WINS, HUMAN_WINS, TIE,        AGENT_WINS, HUMAN_WINS },
  /* Sp */   { HUMAN_WINS, AGENT_WINS, HUMAN_WINS, TIE,        AGENT_WINS },
  /* L  */   { AGENT_WINS, HUMAN_WINS, AGENT_WINS, HUMAN_WINS, TIE }
};

// --- User Interface ---
static void print_title(void) {
  puts("Welcome to Rock–Paper–Scissors–Spock–Lizard!");
}

static void flush_line(void) {
  int c;
  do { c = getchar(); } while (c != '\n');
}

static char read_menu_choice(void) {
  for (;;) {
    puts("\n(S) Single player");
    puts("(E) Exit");
    printf("Select an item: ");
    int ch = getchar();
    flush_line();
    if (ch=='s' || ch=='S') return 's';
    if (ch=='e' || ch=='E') return 'e';
    puts("Unknown option. Try again.");
  }
}

static int read_human_shape(void) {
  for (;;) {
    puts("\n Select a shape:");
    printf("0:%s%s  ||  1:%s%s  ||  2:%s%s  ||  3:%s%s  ||  4:%s%s : ",
           SHAPE_NAME[0], SHAPE_EMOJI[0], SHAPE_NAME[1], SHAPE_EMOJI[1],
           SHAPE_NAME[2], SHAPE_EMOJI[2], SHAPE_NAME[3], SHAPE_EMOJI[3],
           SHAPE_NAME[4], SHAPE_EMOJI[4]);
    int ch = getchar();
    flush_line();
    if (isdigit(ch)) {
      int id = ch - '0';
      if (0 <= id && id < SHAPE_COUNT) return id;
    }
    puts("Shape key does not exist. Try again.");
  }
}

// --- Main Program/Logic ---
int main(void) {
  print_title();

  for (;;) {
    if (read_menu_choice() == 'e') return EXIT_SUCCESS;

    srand((unsigned)time(NULL));

    int human_score = 0, agent_score = 0;
    while (human_score < WINNING_SCORE && agent_score < WINNING_SCORE) {
      int human = read_human_shape();
      int agent = rand() % SHAPE_COUNT;
      enum Outcome r = RES[human][agent];

      printf("You   : %s %s\n", SHAPE_NAME[human], SHAPE_EMOJI[human]);
      printf("Agent : %s %s\n", SHAPE_NAME[agent], SHAPE_EMOJI[agent]);

      if (r == HUMAN_WINS) { puts("Result: You win this round!");  ++human_score; }
      else if (r == AGENT_WINS) { puts("Result: Agent wins this round!"); ++agent_score; }
      else { puts("Result: Tie."); }

      printf("Score  %d:%d\n", human_score, agent_score);
    }

    puts(human_score >= WINNING_SCORE ? "\n You won!" : "\n Agent won!");
  }
}

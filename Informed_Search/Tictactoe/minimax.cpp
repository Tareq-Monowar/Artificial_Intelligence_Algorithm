#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define vi vector<ll>
#define vc vector<char>
#define vvc vector<vc>
#define ump unordered_map<ll, int>
#define ump2 unordered_map<char, int>
#define pi pair<int, int>
#define vp vector<pair<ll, ll>>
#define faster_hridoy            \
    ios::sync_with_stdio(false); \
    cin.tie(NULL);               \
    cout.tie(NULL)
#define yes cout << "Yes\n"
#define no cout << "No\n"
#define rep(i, d, n) for (auto i = d; i < n; i++)
#define pb push_back
#define ft first
#define sd second
#define lcm(a, b) (a * b / __gcd(a, b))
#define rall(a) (a).rbegin(), (a).rend()
#define all(a) (a).begin(), (a).end()
#define mem(x, a) memset(x, a, sizeof(x))
#define input(a)       \
    for (auto &it : a) \
    cin >> it
#define print(a)          \
    for (auto &x : a)     \
    {                     \
        cout << x << ' '; \
    }                     \
    cout << endl
#define endl '\n'
#define PI 3.1415926535897932384
const ll sz = 1e5 + 7;
const int MX = 1e9 + 7;
const ll inf = 1e18 + 7;
const ll mod = 998244353;
// if(x&1==1)odd else even
// if(x&(x-1)==0)power of two else not.(00100-1=00011&00100=00000)
const char PLAYER1 = 'X', PLAYER2 = 'O', EMPTY = '.';
char AI = 'O', HUMAN = 'X';

void printBoard(vvc &board) {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "---+---+---\n";
    }
    cout << "\n";
}

bool movesLeft(vvc &board) {
    for (auto &row : board)
        for (char cell : row)
            if (cell == EMPTY) return true;
    return false;
}

int evaluate(vvc &board) {
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == AI) return +10;
            else if (board[row][0] == HUMAN) return -10;
        }
    }
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == AI) return +10;
            else if (board[0][col] == HUMAN) return -10;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == AI) return +10;
        else if (board[0][0] == HUMAN) return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == AI) return +10;
        else if (board[0][2] == HUMAN) return -10;
    }
    return 0;
}

int minimax(vvc &board, int depth, bool isMax) {
    int score = evaluate(board);
    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (!movesLeft(board)) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = AI;
                    best = max(best, minimax(board, depth + 1, false));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = HUMAN;
                    best = min(best, minimax(board, depth + 1, true));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

pi findBestMove(vvc &board) {
    int bestVal = -1000;
    pi bestMove = {-1, -1};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = AI;
                int moveVal = minimax(board, 0, false);
                board[i][j] = EMPTY;
                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

bool isWin(vvc &board, char player) {
    return evaluate(board) == (player == AI ? 10 : -10);
}

int main() {
    faster_hridoy;
    vvc board(3, vector<char>(3, EMPTY));
    int mode = 2;
    char sym = 'X';

    cout << "Tic-Tac-Toe\n";
    cout << "1. Play with Person\n";
    cout << "2. Play with Computer\n";
    cout << "Choose mode (default 2): " << endl;
    cout.flush();

    if (!(cin >> mode)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        mode = 2;
    }

    if (mode == 2) {
        cout << "Press X to start your turn: " << endl;
        cout.flush();
        if (!(cin >> sym)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            sym = 'X';
        }
        sym = toupper(sym);
        HUMAN = sym;
        AI = (sym == 'X') ? 'O' : 'X';
    }

    int turn = 0;
    while (true) {
        printBoard(board);
        if (mode == 1) {
            int row, col;
            cout << "Player " << (turn == 0 ? "1 (X)" : "2 (O)") << " enter (row col): ";
            cout.flush();
            if (!(cin >> row >> col)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Try again.\n";
                continue;
            }
            row--; col--;
            if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != EMPTY) {
                cout << "Invalid move. Try again.\n";
                continue;
            }
            board[row][col] = (turn == 0) ? PLAYER1 : PLAYER2;
            if (isWin(board, (turn == 0) ? PLAYER1 : PLAYER2)) {
                printBoard(board);
                cout << "Player " << (turn == 0 ? "1" : "2") << " wins!\n";
                break;
            }
            if (!movesLeft(board)) {
                printBoard(board);
                cout << "Draw!\n";
                break;
            }
            turn ^= 1;
        }
        else {
            if ((turn == 0 && HUMAN == 'X') || (turn == 1 && HUMAN == 'O')) {
                int row, col;
                cout << "Enter your move (row col): ";
                cout.flush();
                if (!(cin >> row >> col)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Try again.\n";
                    continue;
                }
                row--; col--;
                if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != EMPTY) {
                    cout << "Invalid move. Try again.\n";
                    continue;
                }
                board[row][col] = HUMAN;
                if (isWin(board, HUMAN)) {
                    printBoard(board);
                    cout << "You win!\n";
                    break;
                }
            }
            else {
                cout << "Computer's move...\n";
                pi aiMove = findBestMove(board);
                board[aiMove.first][aiMove.second] = AI;
                if (isWin(board, AI)) {
                    printBoard(board);
                    cout << "Computer wins!\n";
                    break;
                }
            }
            if (!movesLeft(board)) {
                printBoard(board);
                cout << "Draw!\n";
                break;
            }
            turn ^= 1;
        }
    }
}

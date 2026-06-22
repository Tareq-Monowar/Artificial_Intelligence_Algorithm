#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define vi vector<ll>
#define vc vector<char>
#define vvc vector<vc>
#define ump unordered_map<ll, int>
#define ump2 unordered_map<char, int>
#define pii pair<int,int>
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

void printBoard(const vvc& board) {
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

bool movesLeft(const vvc& board) {
    for (const auto& row : board)
        for (char cell : row)
            if (cell == EMPTY) return true;
    return false;
}

bool isWin(const vvc& board, char player) {

    for (int i = 0; i < 3; i++)
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;

    for (int j = 0; j < 3; j++)
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
            return true;

    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    return false;
}

pii findAnyMove(vvc& board) {

    if (board[1][1] == EMPTY) return {1, 1};


    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == EMPTY)
                return {i, j};

    return {-1, -1};
}

int main() {
    vvc board(3, vector<char>(3, EMPTY));
    int mode = 2;
    char sym = 'X';

    cout << "Tic-Tac-Toe\n";
    cout << "1. Play with Person\n";
    cout << "2. Play with Computer\n";
    cout << "Choose mode (default 2): ";

    if (!(cin >> mode)) {
        cin.clear();
        cin.ignore();
        mode = 2;
    }

    if (mode == 2) {
        cout << "Press X to start your turn: ";
        if (!(cin >> sym)) {
            cin.clear();
            cin.ignore();
            sym = 'X';
        }
        sym = toupper(sym);
        HUMAN = sym;
        AI = (sym == 'X') ? 'O' : 'X';
    }

    int turn = 0;
    while (true) {
        printBoard(board);

        if (mode == 1 || (turn == 0 && HUMAN == 'X') || (turn == 1 && HUMAN == 'O')) {
            int row, col;
            cout << (mode == 1 ?
                   "Player " + string(turn == 0 ? "1 (X)" : "2 (O)") + " enter (row col): " :
                   "Enter your move (row col): ");

            if (!(cin >> row >> col)) {
                cin.clear();
                cin.ignore();
                cout << "Invalid input. Try again.\n";
                continue;
            }
            row--; col--;

            if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != EMPTY) {
                cout << "Invalid move. Try again.\n";
                continue;
            }

            board[row][col] = (mode == 1) ? (turn == 0 ? PLAYER1 : PLAYER2) : HUMAN;

            if (isWin(board, board[row][col])) {
                printBoard(board);
                cout << (mode == 1 ? "Player " + to_string(turn + 1) : "You") << " win!\n";
                break;
            }
        }
        else {
            cout << "Computer's move...\n";
            auto move = findAnyMove(board);
            board[move.first][move.second] = AI;

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
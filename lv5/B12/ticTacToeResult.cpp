#include <iostream>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <optional>
#include <vector>
#include <cstdlib>
#include <random>
#include <string>

using namespace std;
using namespace std::placeholders;

using Line = vector<char>;
using Board = vector<Line>;
using Lines = vector<Line>;

template <typename DestinationType>
auto transformAll = [](const auto &source, auto fn)
{
    DestinationType result;
    result.reserve(source.size());
    transform(source.begin(), source.end(), back_inserter(result), fn);
    return result;
};

auto toRange = [](const auto &collection)
{
    vector<int> range(collection.size());
    iota(begin(range), end(range), 0);
    return range;
};

auto accumulateAll = [](const auto source, auto fn)
{
    return accumulate(source.begin(), source.end(), typename decltype(source)::value_type(), fn);
};

auto all_of_collection = [](const auto &collection, auto fn)
{
    return all_of(collection.begin(), collection.end(), fn);
};

auto any_of_collection = [](const auto &collection, auto fn)
{
    return any_of(collection.begin(), collection.end(), fn);
};

auto lineToString = [](const auto &line)
{
    return transformAll<string>(line, [](auto const token) -> char
                                { return token; });
};

auto boardToLinesString = [](const auto &board)
{
    return transformAll<vector<string>>(board, lineToString);
};

auto boardToString = [](const auto &board)
{
    const auto linesAsString = boardToLinesString(board);
    return accumulateAll(linesAsString,
                         [](string current, string lineAsString)
                         { return current + lineAsString + "\n"; });
};

auto concatenate = [](const auto &first, const auto &second)
{
    auto result{first};
    result.insert(result.end(), make_move_iterator(second.begin()), make_move_iterator(second.end()));
    return result;
};

auto concatenate3 = [](const auto &first, const auto &second, const auto &third)
{
    return concatenate(concatenate(first, second), third);
};

using Coordinate = pair<int, int>;

auto accessAtCoordinates = [](const auto &board, const Coordinate &coordinate)
{
    return board[coordinate.first][coordinate.second];
};

auto projectCoordinates = [](const auto &board, const auto &coordinates)
{
    const auto boardElementFromCoordinates = bind(accessAtCoordinates, board, _1);
    return transformAll<Line>(coordinates, boardElementFromCoordinates);
};

auto mainDiagonalCoordinates = [](const auto &board)
{
    const auto range = toRange(board);
    return transformAll<vector<Coordinate>>(range, [](const auto &index)
                                            { return make_pair(index, index); });
};

auto secondaryDiagonalCoordinates = [](const auto &board)
{
    const auto range = toRange(board);
    return transformAll<vector<Coordinate>>(range, [board](auto index)
                                            { return make_pair(index, board.size() - index - 1); });
};

auto columnCoordinates = [](const auto &board, const auto &columnIndex)
{
    const auto range = toRange(board);
    return transformAll<vector<Coordinate>>(range, [columnIndex](const auto &index)
                                            { return make_pair(index, columnIndex); });
};

auto lineCoordinates = [](const auto &board, const auto &lineIndex)
{
    const auto range = toRange(board);
    return transformAll<vector<Coordinate>>(range, [lineIndex](const auto &index)
                                            { return make_pair(lineIndex, index); });
};

auto mainDiagonal = [](const auto &board)
{
    return projectCoordinates(board, mainDiagonalCoordinates(board));
};

auto secondaryDiagonal = [](const auto &board)
{
    return projectCoordinates(board, secondaryDiagonalCoordinates(board));
};

auto column = [](const auto &board, const auto &columnIndex)
{
    return projectCoordinates(board, columnCoordinates(board, columnIndex));
};

auto line = [](const auto &board, const int lineIndex)
{
    return projectCoordinates(board, lineCoordinates(board, lineIndex));
};

auto allLines = [](const auto &board)
{
    const auto range = toRange(board);
    return transformAll<Lines>(range, [board](auto index)
                               { return line(board, index); });
};

auto allColumns = [](const auto &board)
{
    const auto range = toRange(board);
    return transformAll<Lines>(range, [board](auto index)
                               { return column(board, index); });
};

auto allDiagonals = [](const auto &board) -> Lines
{
    return {mainDiagonal(board), secondaryDiagonal(board)};
};

template <typename SourceType, typename DestinationType>
auto applyAllLambdasToValue = [](const auto &fns, const auto &value)
{
    return transformAll<DestinationType>(fns, [value](const auto &fn)
                                         { return fn(value); });
};

auto allLinesColumnsAndDiagonals = [](const auto &board)
{
    return concatenate3(allLines(board), allColumns(board), allDiagonals(board));
};

auto lineFilledWith = [](const auto &line, const auto &tokenToCheck)
{
    return all_of_collection(line, [&tokenToCheck](const auto &token)
                             { return token == tokenToCheck; });
};

auto lineFilledWithX = bind(lineFilledWith, _1, 'X');
auto lineFilledWithO = bind(lineFilledWith, _1, 'O');

template <typename CollectionBooleanOperation, typename CollectionProvider, typename Predicate>
auto booleanOperationOnProvidedCollection(CollectionBooleanOperation collectionBooleanOperation, CollectionProvider collectionProvider, Predicate predicate)
{
    return [=](auto collectionProviderSeed, auto predicateFirstParameter)
    {
        return collectionBooleanOperation(collectionProvider(collectionProviderSeed),
                                          bind(predicate, _1, predicateFirstParameter));
    };
}

auto tokenWins = booleanOperationOnProvidedCollection(any_of_collection, allLinesColumnsAndDiagonals, lineFilledWith);
auto xWins = bind(tokenWins, _1, 'X');
auto oWins = bind(tokenWins, _1, 'O');

/*auto xWins = [](const auto& board){
    return any_of_collection(allLinesColumnsAndDiagonals(board), lineFilledWithX);
};

auto oWins = [](const auto& board){
    return any_of_collection(allLinesColumnsAndDiagonals(board), lineFilledWithO);
};
*/

/* auto noneOf = [](const auto& collection, const auto& fn){
    return none_of(collection.begin(), collection.end(), fn);
};*/

// auto isEmpty = [](const auto& token){return token == ' ';};

auto isNotEmpty = [](const auto &token)
{ return token != ' '; };

auto fullLine = bind(all_of_collection, _1, isNotEmpty);

auto full = [](const auto &board)
{
    return all_of_collection(board, fullLine);
};

auto draw = [](const auto &board)
{
    return full(board) && !xWins(board) && !oWins(board);
};

auto inProgress = [](const auto &board)
{
    return !full(board) && !xWins(board) && !oWins(board);
};

auto findInCollection = [](const auto &collection, const auto &fn)
{
    const auto result = find_if(collection.begin(), collection.end(), fn);
    return (result == collection.end()) ? nullopt : optional(*result);
};

auto findInCollectionWithDefault = [](const auto &collection, const auto &defaultResult, const auto &fn)
{
    const auto result = findInCollection(collection, fn);
    return result.has_value() ? (*result) : defaultResult;
};

auto howDidXWin = [](auto const board)
{
    map<string, Line> linesWithDescription{
        {"first line", line(board, 0)},
        {"second line", line(board, 1)},
        {"last line", line(board, 2)},
        {"first column", column(board, 0)},
        {"second column", column(board, 1)},
        {"last column", column(board, 2)},
        {"main diagonal", mainDiagonal(board)},
        {"secondary diagonal", secondaryDiagonal(board)},
        {"diagonal", secondaryDiagonal(board)},
    };
    auto xDidNotWin = make_pair("X did not win", Line{});
    auto xWon = [](auto value)
    {
        return lineFilledWithX(value.second);
    };

    return findInCollectionWithDefault(linesWithDescription, xDidNotWin, xWon).first;
};

// self written Tests

auto sum_of_token_in_line = [](const auto &board, const char token)
{
    return accumulateAll(boardToString(board), [token](int currentCount, char c)
                         { return currentCount + (c == token ? 1 : 0); });
};

auto valid_plays = [](const auto &board)
{
    return abs(sum_of_token_in_line(board, 'X') - sum_of_token_in_line(board, 'O')) <= 1;
};

auto invalid_played = [](const auto &board)
{
    return abs(sum_of_token_in_line(board, 'X') - sum_of_token_in_line(board, 'O')) > 1;
};

TEST_CASE("Correct Tokens played - 1 difference")
{

    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};

    CHECK_EQ(true, valid_plays(board));
}

TEST_CASE("Correct Tokens played - 0 difference")
{

    Board board{
        {'X', ' ', 'X'},
        {'X', 'O', ' '},
        {'O', ' ', 'O'}};

    CHECK_EQ(true, valid_plays(board));
}

TEST_CASE("Invalid Tokens played")
{

    Board board{
        {'X', ' ', 'X'},
        {'X', ' ', ' '},
        {'O', ' ', ' '}};

    CHECK_EQ(false, valid_plays(board));
}

// 2 und 3

auto isValidToken = [](const auto token)
{
    return token == 'X' || token == 'O' || token == ' ';
};

auto isValidBoard = [](const auto &board)
{
    return all_of_collection(board, [](const auto &row)
                             { return all_of_collection(row, isValidToken); });
};

TEST_CASE("Valid board")
{

    Board board{
        {'X', ' ', 'X'},
        {'X', ' ', ' '},
        {'O', ' ', ' '},
    };

    CHECK_EQ(true, isValidBoard(board));
}

TEST_CASE("Invalid board")
{

    Board board{
        {'X', ' ', 'X'},
        {'X', ' ', ' '},
        {'O', 'F', ' '},
    };

    CHECK_EQ(false, isValidBoard(board));
}

// board.size == 3 überprüft ob das Board 3 Zeilen hat
//  all_of(board.begin(), board.end(),
//[](const Line &line) { return line.size() == 3; }); überprüft ob jede Zeile 3 Spalten hat => überüft ob jede Zeile 3 Spalten hat

bool isValidDimensions(const Board &board)
{
    return board.size() == 3 && all_of_collection(board, [](const Line &line)
                                                  { return line.size() == 3; });
}

TEST_CASE("Invalid Lines")
{

    Board board{
        {'X', ' ', 'X'},
        {'X', ' ', ' '},
        {'O', ' ', ' '},
        {'O', ' ', ' '}};

    CHECK_EQ(false, isValidDimensions(board));
}

TEST_CASE("Invalid Colums")
{

    Board board{
        {'X', ' ', 'X', ' '},
        {'X', ' ', ' '},
        {'O', ' ', ' '},
    };

    CHECK_EQ(false, isValidDimensions(board));
}

TEST_CASE("Valid Board")
{

    Board board{
        {'X', ' ', 'X'},
        {'X', ' ', ' '},
        {'O', ' ', ' '},
    };

    CHECK_EQ(true, isValidDimensions(board));
}

//=====================================================

TEST_CASE("lines")
{
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};

    Line expectedLine0{'X', 'X', 'X'};
    CHECK_EQ(expectedLine0, line(board, 0));
    Line expectedLine1{' ', 'O', ' '};
    CHECK_EQ(expectedLine1, line(board, 1));
    Line expectedLine2{' ', ' ', 'O'};
    CHECK_EQ(expectedLine2, line(board, 2));
}

TEST_CASE("all columns")
{
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};

    Line expectedColumn0{'X', ' ', ' '};
    CHECK_EQ(expectedColumn0, column(board, 0));
    Line expectedColumn1{'X', 'O', ' '};
    CHECK_EQ(expectedColumn1, column(board, 1));
    Line expectedColumn2{'X', ' ', 'O'};
    CHECK_EQ(expectedColumn2, column(board, 2));
}

TEST_CASE("main diagonal")
{
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};

    Line expectedDiagonal{'X', 'O', 'O'};

    CHECK_EQ(expectedDiagonal, mainDiagonal(board));
}

TEST_CASE("secondary diagonal")
{
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};

    Line expectedDiagonal{'X', 'O', ' '};

    CHECK_EQ(expectedDiagonal, secondaryDiagonal(board));
}

TEST_CASE("all lines, columns and diagonals")
{
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};

    Lines expected{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'},
        {'X', ' ', ' '},
        {'X', 'O', ' '},
        {'X', ' ', 'O'},
        {'X', 'O', 'O'},
        {'X', 'O', ' '}};

    auto all = allLinesColumnsAndDiagonals(board);
    CHECK_EQ(expected, all);
}

TEST_CASE("line to string")
{
    Line line{
        ' ', 'X', 'O'};

    CHECK_EQ(" XO", lineToString(line));
}

TEST_CASE("board to lines string")
{
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};
    vector<string> expected{
        "XXX",
        " O ",
        "  O"};

    CHECK_EQ(expected, boardToLinesString(board));
}

TEST_CASE("board to string")
{
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};
    string expected{"XXX\n O \n  O\n"};

    CHECK_EQ(expected, boardToString(board));
}

TEST_CASE("Line filled with X")
{
    Line line{'X', 'X', 'X'};

    CHECK(lineFilledWithX(line));
}

TEST_CASE("Line not filled with X")
{
    CHECK(!lineFilledWithX(Line({'X', 'O', 'X'})));
    CHECK(!lineFilledWithX(Line({'X', ' ', 'X'})));
}

TEST_CASE("X wins")
{
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};

    CHECK(xWins(board));
}

TEST_CASE("O wins")
{
    Board board{
        {'X', 'O', 'X'},
        {' ', 'O', ' '},
        {' ', 'O', 'X'}};

    CHECK(oWins(board));
}

TEST_CASE("draw")
{
    Board board{
        {'X', 'O', 'X'},
        {'O', 'O', 'X'},
        {'X', 'X', 'O'}};

    CHECK(draw(board));
}

TEST_CASE("in progress")
{
    Board board{
        {'X', 'O', 'X'},
        {'O', ' ', 'X'},
        {'X', 'X', 'O'}};

    CHECK(inProgress(board));
}

TEST_CASE("how did X win")
{
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};

    CHECK_EQ("first line", howDidXWin(board));
}

TEST_CASE("X did not win")
{
    Board board{
        {'X', 'X', ' '},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};

    CHECK_EQ("X did not win", howDidXWin(board));
}

TEST_CASE("Project column")
{
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};

    Line expected0{'X', ' ', ' '};
    CHECK_EQ(expected0, column(board, 0));
    Line expected1{'X', 'O', ' '};
    CHECK_EQ(expected1, column(board, 1));
    Line expected2{'X', ' ', 'O'};
    CHECK_EQ(expected2, column(board, 2));
}

TEST_CASE("Range")
{
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};

    vector<int> expected = {0, 1, 2};
    CHECK_EQ(expected, toRange(board));
    CHECK_EQ(expected, toRange(board[0]));
}

// Property Based Testing

using Generator = std::function<Board()>;

using Property = std::function<bool(const Board)>;

auto check_property = [](const Generator generator, Property property, size_t size = 100) -> bool
{
    bool returnValue = true;
    for (size_t i = 0; i < size; i++)
    {
        auto board = generator(); // Zufälliges Board generieren

        bool propertyHolds = property(board);

        CHECK(propertyHolds);

        if (!propertyHolds)
        {
            returnValue = false;
        }
    }

    return returnValue;
};

// 1. Generator
auto generateRandomTicTacToeBoard = []() -> Board
{
    char EMPTY = ' ';
    char X_TOKEN = 'X';
    char O_TOKEN = 'O';
    Board board(3, Line(3, EMPTY));
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, 2);

    int numX = 0;
    int numO = 0;
    int currentPlayer = X_TOKEN;

    while (numX + numO < 9)
    {
        int row = distribution(generator);
        int col = distribution(generator);

        if (board[row][col] == EMPTY)
        {
            board[row][col] = currentPlayer;
            currentPlayer = (currentPlayer == X_TOKEN) ? O_TOKEN : X_TOKEN;

            if (currentPlayer == X_TOKEN)
            {
                numX++;
            }
            else
            {
                numO++;
            }
        }
    }

    return board;
};

auto property_fully_filled_board = [](const Board &board)
{
    return all_of(board.begin(), board.end(), [](const vector<char> &row)
                  { return all_of(row.begin(), row.end(), [](char cell)
                                  { return cell != ' '; }); });
};

TEST_CASE("1. Generator Test")
{
    check_property(generateRandomTicTacToeBoard, property_fully_filled_board);
}

// 2. Generator
auto generateErroneousBoard = []() -> Board
{
    random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 2);

    int x = dist(gen);
    int y = dist(gen);

    Board board = generateRandomTicTacToeBoard();

    board[x][y] = 'A';

    return board;
};

auto property_has_erroneous_token = [](const Board board) -> bool
{
    for (const auto &row : board)
    {
        for (char cell : row)
        {
            if (cell != 'X' || cell != 'O')
            {
                return true;
            }
        }
    }
    return false;
};

TEST_CASE("2. Generator Test")
{
    check_property(generateErroneousBoard, property_has_erroneous_token);
    check_property(generateErroneousBoard, property_fully_filled_board);
}

// 3. Generator

auto partially_filled_board_correct = []() -> Board
{
    char EMPTY = ' ';
    char X_TOKEN = 'X';
    char O_TOKEN = 'O';
    Board board(3, Line(3, EMPTY));
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, 2);

    int numX = 0;
    int numO = 0;
    int currentPlayer = X_TOKEN;
    uniform_int_distribution<int> dist2(1, 8);
    int maxFilled = dist2(generator);

    while (numX + numO < maxFilled)
    {
        int row = distribution(generator);
        int col = distribution(generator);

        if (board[row][col] == EMPTY)
        {
            board[row][col] = currentPlayer;
            currentPlayer = (currentPlayer == X_TOKEN) ? O_TOKEN : X_TOKEN;

            if (currentPlayer == X_TOKEN)
            {
                numX++;
            }
            else
            {
                numO++;
            }
        }
    }

    return board;
};

auto property_has_empty_cell = [](const Board &board) -> bool
{
    for (const auto &row : board)
    {
        for (char cell : row)
        {
            if (cell == ' ')
            {
                return true; // Found an empty cell
            }
        }
    }
    return false; // No empty cells found
};

auto property_only_valid_chars = [](const Board &board)
{
    for (const auto &row : board)
    {
        for (char cell : row)
        {
            if (cell != 'X' && cell != 'O' && cell != ' ')
            {
                return false; // Found an invalid character
            }
        }
    }
    return true; // All characters are valid ('X', 'O', or ' ')
};

TEST_CASE("3. Generator Test")
{
    check_property(partially_filled_board_correct, property_has_empty_cell);
    check_property(partially_filled_board_correct, property_only_valid_chars);
    check_property(partially_filled_board_correct, isValidDimensions);
    check_property(partially_filled_board_correct, isValidBoard);
}

// 4. Generator
auto generateBoardWithInvalidMoves = []() -> Board
{
    random_device rd;
    mt19937 gen(rd());

    Board board(3, Line(3, ' '));

    int xCount = 0;
    int oCount = 0;

    // Ensure there is an error in token distribution (minimum difference of 2)
    while (abs(xCount - oCount) <= 1)
    {
        xCount = uniform_int_distribution<int>(0, 4)(gen);
        oCount = uniform_int_distribution<int>(0, 4)(gen);
    }

    // Place 'X' tokens
    for (int i = 0; i < xCount; ++i)
    {
        int row, col;
        do
        {
            row = uniform_int_distribution<int>(0, 2)(gen);
            col = uniform_int_distribution<int>(0, 2)(gen);
        } while (board[row][col] != ' ');
        board[row][col] = 'X';
    }

    // Place 'O' tokens
    for (int i = 0; i < oCount; ++i)
    {
        int row, col;
        do
        {
            row = uniform_int_distribution<int>(0, 2)(gen);
            col = uniform_int_distribution<int>(0, 2)(gen);
        } while (board[row][col] != ' ');
        board[row][col] = 'O';
    }

    return board;
};

auto property_invalid_moves(const Board &board)
{
    return invalid_played(board);
}

TEST_CASE("4. Generator Test")
{
    check_property(generateBoardWithInvalidMoves, property_has_empty_cell);
    check_property(generateBoardWithInvalidMoves, property_invalid_moves);
}

// 5. Generator

// auto generateRandomWinningBoard = []() -> Board
// {
//     Board board(3, Line(3, ' '));
//     random_device rd;
//     mt19937 gen(rd());

//     uniform_int_distribution<int> winningPlayer(0, 1);
//     char winner = (winningPlayer(gen) == 0) ? 'X' : 'O';

//     vector<pair<int, int>> availablePositions;  // Vector welcehr speichert welche Positionen noch spielbar sind

//     for (int i = 0; i < 3; ++i)  // Diese doppelte Schleife dient dazu um alle Möglichen Positionen in den vector hinzuzufügen
//     {
//         for (int j = 0; j < 3; ++j)
//         {
//             availablePositions.push_back(make_pair(i, j));
//         }
//     }

//     shuffle(availablePositions.begin(), availablePositions.end(), gen); // Zufällige Reihenfolge wird festgelegt, sprich welcher Move wan dran ist.

//     //Bestimmt welche Linie gewinnt
//     uniform_int_distribution<int> winningLineType(0, 2);
//     int lineType = winningLineType(gen);

//     int countX = 0;
//     int countO = 0;

//     // Fill the board with valid moves
//     for (int move = 0; move < 9; ++move)
//     {
//         int row = availablePositions[move].first;
//         int col = availablePositions[move].second;

//         if (countX == 5 && winner == 'X')
//         {
//             board[row][col] = 'O';
//             countO++;
//         }
//         else if (countO == 5 && winner == 'O')
//         {
//             board[row][col] = 'X';
//             countX++;
//         }
//         else
//         {
//             board[row][col] = winner;
//             if (winner == 'X')
//             {
//                 countX++;
//             }
//             else
//             {
//                 countO++;
//             }
//         }

//         // Check if the current player wins
//         if (move >= 4)
//         {
//             // Check rows, columns, and diagonals
//             if ((lineType == 0 && board[row][0] == winner && board[row][1] == winner && board[row][2] == winner) ||
//                 (lineType == 1 && board[0][col] == winner && board[1][col] == winner && board[2][col] == winner) ||
//                 (lineType == 2 && ((row == 0 && col == 0 && board[0][0] == winner && board[1][1] == winner && board[2][2] == winner) ||
//                                    (row == 0 && col == 2 && board[0][2] == winner && board[1][1] == winner && board[2][0] == winner))))
//             {
//                 return board; // Player wins, return the board
//             }
//         }

//         // Switch to the other player
//         winner = (winner == 'X') ? 'O' : 'X';
//     }

//     return board; // If no winner, return the current state of the board
// };

auto generateOnlyWinner = []()
{
    while (true)
    {
        auto board = generateRandomTicTacToeBoard();
        if (xWins(board) || oWins(board))
        {
            return board;
        }
    }
};

auto property_hasWinner = [](const Board &board)
{
    return xWins(board) || oWins(board);
};

TEST_CASE("5. Generator Test")
{
    check_property(generateOnlyWinner, property_hasWinner);
    check_property(generateOnlyWinner, valid_plays);
    check_property(generateOnlyWinner, property_fully_filled_board);
}

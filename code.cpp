using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace Tetris
{
    class Tetris
    {
        static void Main(string[] args)
        {
            Console.Title = "Tetris";
            Console.SetWindowSize(40, 40);
            Console.SetBufferSize(40, 40);
            Console.CursorVisible = false;

            Game game = new Game();
            game.Run();
        }
    }

    class Game
    {
        private int width = 10;
        private int height = 20;
        private int[,] board;
        private bool gameOver;
        private int score;
        private int delay;

        private Shape currentShape;
        private int currentX;
        private int currentY;

        private Random rand;

        public Game()
        {
            board = new int[width, height];
            rand = new Random();
            delay = 200;
        }

        public void Run()
        {
            while (!gameOver)
            {
                Update();
                Draw();
                Thread.Sleep(delay);
            }

            Console.Clear();
            Console.WriteLine("Game over. Your score: " + score);
            Console.ReadKey();
        }

        private void Update()
        {
            if (currentShape == null)
            {
                currentShape = GetRandomShape();
                currentX = width / 2 - currentShape.Width / 2;
                currentY = 0;
            }
            else
            {
                if (CanMoveDown())
                {
                    currentY++;
                }
                else
                {
                    AddShapeToBoard();
                    currentShape = null;
                    CheckLines();
                }
            }

            if (Console.KeyAvailable)
            {
                ConsoleKeyInfo key = Console.ReadKey(true);
                if (key.Key == ConsoleKey.LeftArrow && CanMoveLeft())
                {
                    currentX--;
                }
                else if (key.Key == ConsoleKey.RightArrow && CanMoveRight())
                {
                    currentX++;
                }
                else if (key.Key == ConsoleKey.Spacebar && CanRotate())
                {
                    currentShape.Rotate();
                }
                else if (key.Key == ConsoleKey.DownArrow)
                {
                    delay = 10;
                }
            }
            else
            {
                delay = 200;
            }
        }

        private void Draw()
        {
            Console.Clear();

            DrawBoard();

            if (currentShape != null)
            {
                DrawShape(currentShape, currentX, currentY);
            }

            Console.WriteLine("Score: " + score);
        }

        private void DrawBoard()
        {
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    if (board[x, y] == 1)
                    {
                        Console.SetCursorPosition(x, y);
                        Console.Write("█");
                    }
                    else
                    {
                        Console.SetCursorPosition(x, y);
                        Console.Write(" ");
                    }
                }
            }
        }

        private void DrawShape(Shape shape, int x, int y)
        {
            for (int i = 0; i < shape.Width; i++)
            {
                for (int j = 0; j < shape.Height; j++)
                {
                    if (shape[i, j] == 1)
                    {
                        Console.SetCursorPosition(x + i, y + j);
                        Console.Write("█");
                    }
                }
            }
        }

        private Shape GetRandomShape()
        {
            int shapeIndex = rand.Next(7);
            Shape shape = null;

            switch (shapeIndex)

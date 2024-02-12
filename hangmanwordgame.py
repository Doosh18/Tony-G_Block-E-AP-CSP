import random
#dictionary
words_dict = {
    2: ["no", "if", "it"],
    3: ["cat", "run", "bat"],
    4: ["bird", "fish", "lion"],
    5: ["mouse", "heard", "tiger"],
}
# Scoreboard dictionary
scoreboard = {}
# Function to display menu
def display_menu():
    print("Hangman Game Menu")
    print("1. Instructions")
    print("2. Select word with 2 letters")
    print("3. Select word with 3 letters")
    print("4. Select word with 4 letters")
    print("5. Select word with 5 letters")
    print("6. Random word selection")
    print("7. Scoreboard")
    print("8. Exit")
# Function to display instructions
def display_instructions():
    print("Hangman Game Instructions:")
    print("You have to guess the word by guessing one letter at a time.")
    print("You have as many attempts as the length of your word to guess the word.")
    print("Good luck!")
# Function to select a word from the given length
def select_word(length):
    return random.choice(words_dict[length])
# Function to play hangman game
def play_hangman(word):
    guessed_letters = []
    attempts = len(word) - 1
    guessed_word = ["_"] * len(word)
    while attempts > 0:
        print(" ".join(guessed_word))
        guess = input("Enter a letter: ").lower()
        if guess in guessed_letters:
            print("You already guessed that letter!")
            continue
        guessed_letters.append(guess)
        if guess in word:
            print("Correct!")
            for i in range(len(word)):
                if word[i] == guess:
                    guessed_word[i] = guess
        else:
            print("Incorrect guess. You have {} attempts left.".format(attempts))
            attempts -= 1

        if "_" not in guessed_word:
            print("Congratulations! You guessed the word:", "".join(guessed_word))
            name = input("Enter your name: ")
            return name, attempts

    print("You ran out of attempts. The word was:", word)
    return None, 0

# Function to display scoreboard ( I had to look this one up )
def display_scoreboard():
    print("Scoreboard:")
    for i, (name, score) in enumerate(sorted(scoreboard.items(), key=lambda x: x[1], reverse=True), 1):
        print(f"{i}. {name}: {score}")

# Main function
def main():
    while True:
        display_menu()
        choice = input("Enter your choice: ")
        if choice == "1":
            display_instructions()
        elif choice in ["2", "3", "4", "5"]:
            length = int(choice)
            word = select_word(length)
            name, score = play_hangman(word)
            if name:
                if name in scoreboard:
                    scoreboard[name] = max(scoreboard[name], score)
                else:
                    scoreboard[name] = score
        elif choice == "6":
            length = random.choice([2, 3, 4, 5])
            word = select_word(length)
            name, score = play_hangman(word)
            if name:
                if name in scoreboard:
                    scoreboard[name] = max(scoreboard[name], score)
                else:
                    scoreboard[name] = score
        elif choice == "7":
            display_scoreboard()
        elif choice == "8":
            print("Exiting the game")
            break
        else:
            print("Invalid choice")

if __name__ == "__main__":
    main()

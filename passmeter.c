#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h> // for tolower()
#include <time.h>
#include <stdlib.h>
/**
 *
 * A password strength meter and a default password generator, 
 * as defined in the CS221 course website for Project 1.
 *
 */

	// method chekcs if the password is strong
	bool isStrongPassword(const char * username, const char * password) {
		// checks if the password is at least 8 characters long
		if (strlen(password) < 8) { 
			return false;
		}

		bool has_uppercase = false;
		bool has_lowercase = false;
		bool has_digit = false;
		int consecutive_letters = 0;
		bool has_four_consecutive_letters = false;

		for (int i = 0; i < strlen(password); i++) {
			// checks if the password has a special character
			if (!((password[i] >= 'A' && password[i] <= 'Z') || (password[i] >= 'a' && password[i] <= 'z') || (password[i] >= '0' && password[i] <= '9'))) { 
				return false;
			}
			// checks if the password has consecutive letters
			if ((password[i] >= 'A' && password[i] <= 'Z') || (password[i] >= 'a' && password[i] <= 'z')) { 
				consecutive_letters++;
			} else {
				consecutive_letters = 0;
			}
			// checks if the password has at least 4 consecutive letters
			if (consecutive_letters >= 4) { 
				has_four_consecutive_letters = true;
			}
			// checks if the password has a uppercase
			if (password[i] >= 'A' && password[i] <= 'Z') { 
				has_uppercase = true;
			}
			// checks if the password has a lowercase
			else if (password[i] >= 'a' && password[i] <= 'z') { 
				has_lowercase = true;
			} 
			// checks if the password has a digit
			else if (password[i] >= '0' && password[i] <= '9') { 
				has_digit = true;
			}

			// checks if the password contains the username
			bool username_match = true;
			for (int j = 0; j < strlen(username) && i + j < strlen(password); j++) {
				if (tolower(password[i + j]) != tolower(username[j])) {
					username_match = false;
				}
			}

			// if the password contains the username, it is not a strong password
			if (username_match) {
				return false;
			}
		}

		// if the password does not have at least 4 consecutive letters, it is not a strong password
		if (!has_four_consecutive_letters) {
			return false;
		}

		// if the password does not have a uppercase, a lowercase, and a digit, it is not a strong password
		if (!has_uppercase || !has_lowercase || !has_digit) {
			return false;
		}
		
		// if the password is strong, return true
		return true;
	}

	/** 
	 * Example: isStrongDefaultPassword("vahab", "Taher3h") returns false
	 */
	bool isStrongDefaultPassword(const char* username, const char* password) {
		// Check password length - must be between 8 and 15 characters inclusive
		if (strlen(password) < 7 || strlen(password) > 15) {
			return false;
		}

		bool has_uppercase = false;
		bool has_lowercase = false;
		bool has_digit = false;

		for (int i = 0; i < strlen(password); i++) {
			// checks if the password has a special character
			if (!((password[i] >= 'A' && password[i] <= 'Z') || (password[i] >= 'a' && password[i] <= 'z') || (password[i] >= '0' && password[i] <= '9'))) { 
				return false;
			}
			// checks if the password has a uppercase
			if (password[i] >= 'A' && password[i] <= 'Z') { 
				has_uppercase = true;
			}
			// checks if the password has a lowercase
			else if (password[i] >= 'a' && password[i] <= 'z') { 
				has_lowercase = true;
			} 
			// checks if the password has a digit
			else if (password[i] >= '0' && password[i] <= '9') { 
				has_digit = true;
			}

			// Check if password contains username
			if (i + strlen(username) <= strlen(password)) {
				bool username_match = true;
				for (int j = 0; j < strlen(username); j++) {
					if (tolower(password[i + j]) != tolower(username[j])) {
						username_match = false;
						break;  // Exit as soon as we find a mismatch
					}
				}
				if (username_match) {
					return false;
				}
			}
		}

		// if the password does not have a uppercase, a lowercase, and a digit, it is not a strong password
		if (!has_uppercase || !has_lowercase || !has_digit) {
			return false;
		}
		
		// if the password is strong, return true
		return true;
	}

	/** 
	 * This function may *not* call isStrongPassword(). 
	 * This function must call isStrongDefaultPassword().
	 */
	void generateDefaultPassword(char * default_password, const char * username) {
		int length;
		do {
			length = (rand() % 8) + 8;  // Random length between 8 and 15
			for (int i = 0; i < length; i++) {
				int char_type = rand() % 3; // Randomly choose a character type
				switch (char_type) {
					case 0:
						default_password[i] = 'A' + rand() % 26; // Uppercase letter character choice
						break;
					case 1:
						default_password[i] = 'a' + rand() % 26; // Lowercase letter character choice
						break;
					case 2:
						default_password[i] = '0' + rand() % 10; // Digit character choice
						break;
				}
			}
			default_password[length] = '\0';
		} while (!isStrongDefaultPassword(username, default_password));
	}

	int main(void) 
	{
		// Initialize random seed once at program start
		srand((unsigned int)time(NULL));
		
		char username[100];
		char password[100];
		char default_password[16]; // Increased size to safely hold 15 chars + null terminator
		printf("Enter a username: ");
		scanf("%s", username);
		printf("Generating default password...\n");
		generateDefaultPassword(default_password, username);
		printf("Generated default password: %s\n", default_password);
		printf("Enter new password: ");
		scanf("%s", password);
		printf("%s\n", isStrongPassword(username, password) ? "Strong password!" : "Your password is weak. Try again!");
		return 0;
	}
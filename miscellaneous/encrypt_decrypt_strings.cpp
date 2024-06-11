#include <iostream>
#include <string>

/*
Initially I thought of using a map to store letter associations with numbers. A better option
is to work on the ASCII values of characters themselves.

Basic steps for encryption or decryption: str = string, pwd = password
1. Normalize the password: remove non-alphabets and convert upper case to lower case.
(Or lower case to upper case. Any approach works.)
n = pwd.size()
i = 0  (for password)
2. Start a for loop over str: i = 0:
  a. if  i >= n : i = 0   ( making password application cyclic)
  password character p = pwd [i]
  b. Calculate the shift as shift = p - 'a' for encryption and 
  shift = 'a' - p for decryption.
  c. Add shift to s as s = (s - 'a' + shift + 26)%26 + 'a';
  A similar expression exists for upper case s.
  d. i++
  
  (Input string is passed by reference.)
  
  Since encryption and decryption are so similar, I plan to write an encode function that 
  takes in a boolean argument indicating encryption or decryption.
  This mitigates code repetition.
*/


/**
 @param input_string [out] string to be encrypted or decrypted; string encoded in place.
 @param password password for encryption or decryption.
 @param boolean boolean indicating whether string is to be encrypted (true) or decrypted (false)
*/
void encode(std::string &input_string, std::string password, bool encrypt){
  // Variable to store processed password after removal of non-lower-case alphabets.
  std::string processed_password;
  for (auto &element : password){
    // Consider password char only if an alphabet.
    if (std::isalpha(element)){
      // Convert password char to lower case and add to processed password.
      processed_password += std::tolower(element);
    }
  }

  // Variable keeping track of password letter used for encoding.
  int pwd_count = 0;
  
  for (auto &s : input_string){
    // Get letter from processed password.
    auto p = processed_password[pwd_count % processed_password.size()];
    
    // Do not alter input string character if not alphabet.
    if (!std::isalpha(s)){
      continue;
    }
    
    // Get shift in integer using password letter and alphabet start as reference.
    auto letter_shift = p - 'a';
    if (!encrypt){
      // If decryption, we need to nullify the shift added during encryption.
      letter_shift *= -1;
    }
    
    // Alphabet reference will be used to get the integer value of a character
    // with respect to the 'a' or 'A'.
    char alpha_ref;
    if (std::islower(s)){
      alpha_ref = 'a';
    } else {
      alpha_ref = 'A';
    }
    
    // Normalize the string character with respect to the start of lowercase alphabet.
    s -= alpha_ref;
    // Add shift and handle the case if the normalized value of s spills over 25.
    s = (s + letter_shift + 26) % 26;
    // Add the reference to get encoded letter s.
    s += alpha_ref;
    
    pwd_count++;
  } 
  return;
}

/**
  @param input_string [out] Encrypted input string.
  @param password Password for encryption.
*/
void encrypt(std::string &input_string, std::string password){
  encode(input_string, password, true);
  return;
}

/**
  @param input_string [out] Decrypted input string.
  @param password Password for decryption.
*/
void decrypt(std::string &input_string, std::string password){
  encode(input_string, password, false);
  return;
}


int main() {
  // Test cases
  std::string str = "Hello World!";
  std::string pwd = "abc";
  encrypt(str, pwd);
  std::cout<<"Encrypted String: "<<str<<std::endl;
  decrypt(str, pwd);
  std::cout<<"Decrypted String: "<<str<<std::endl;
	return 0;
}


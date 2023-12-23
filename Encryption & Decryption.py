def encrypt(plaintext, shift):
    ciphertext = ""
    for char in plaintext:
        if char.isalpha():
            shifted_char = chr((ord(char.lower()) - 97 + shift) % 26 + 97)
            if char.isupper():
                shifted_char = shifted_char.upper()
            ciphertext += shifted_char
        else:
            ciphertext += char
    return ciphertext


def decrypt(ciphertext, shift):
    plaintext = ""
    for char in ciphertext:
        if char.isalpha():
            shifted_char = chr((ord(char.lower()) - 97 - shift) % 26 + 97)
            if char.isupper():
                shifted_char = shifted_char.upper()
            plaintext += shifted_char
        else:
            plaintext += char
    return plaintext
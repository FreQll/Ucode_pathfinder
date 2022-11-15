int mx_strlen(const char *s) {
    int length = 0;
    for ( ; s[length] != '\0'; length++);
    return length;
}

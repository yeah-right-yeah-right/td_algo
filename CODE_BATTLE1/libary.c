#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define HASH_KEY 0x9e3779b1u

int encrypt(int id, int key)
{
    // And now for the encryption part
    id ^= key;
    return id;
}

int decrypt(int id, int key)
{
    return encrypt(id, key);
}

typedef struct Node {
    int id;
    struct Node *next;
} Node;

typedef struct HashTable {
    size_t size;    // number of buckets
    Node **buckets; // array of bucket heads
} HashTable;

static unsigned hash_id(int id)
{
    /* Use encrypt as the raw hash value, then interpret as unsigned */
    return (unsigned)encrypt(id, (int)HASH_KEY);
}

HashTable *ht_create(size_t size)
{
    HashTable *ht = malloc(sizeof(HashTable));
    if (!ht) return NULL;
    ht->size = size;
    ht->buckets = calloc(size, sizeof(Node *));
    if (!ht->buckets) {
        free(ht);
        return NULL;
    }
    return ht;
}

int ht_exists(HashTable *ht, int id)
{
    if (!ht || ht->size == 0) return 0;
    unsigned h = hash_id(id);
    size_t idx = (size_t)(h % ht->size);
    for (Node *n = ht->buckets[idx]; n; n = n->next) {
        if (n->id == id) return 1;
    }
    return 0;
}

int ht_insert(HashTable *ht, int id)
{
    if (!ht) return 0;
    if (ht_exists(ht, id)) return 1; // already present
    unsigned h = hash_id(id);
    size_t idx = (size_t)(h % ht->size);
    Node *n = malloc(sizeof(Node));
    if (!n) return 0;
    n->id = id;
    n->next = ht->buckets[idx];
    ht->buckets[idx] = n;
    return 1;
}

void ht_free(HashTable *ht)
{
    if (!ht) return;
    for (size_t i = 0; i < ht->size; ++i) {
        Node *n = ht->buckets[i];
        while (n) {
            Node *tmp = n->next;
            free(n);
            n = tmp;
        }
    }
    free(ht->buckets);
    free(ht);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <inputfile>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("fopen");
        return 1;
    }

    int N;
    if (fscanf(f, "%d", &N) != 1) {
        fprintf(stderr, "Failed to read N (number of books)\n");
        fclose(f);
        return 1;
    }

    if (N < 0) N = 0;

    /* choose a table size (power of two >= 2*N, at least 1) */
    size_t table_size = 1;
    while (table_size < (size_t)N * 2) table_size <<= 1;

    HashTable *ht = ht_create(table_size);
    if (!ht) {
        fprintf(stderr, "Out of memory creating hash table\n");
        fclose(f);
        return 1;
    }

    for (int i = 0; i < N; ++i) {
        int id;
        if (fscanf(f, "%d", &id) != 1) {
            fprintf(stderr, "Failed to read book id at position %d\n", i);
            ht_free(ht);
            fclose(f);
            return 1;
        }
        ht_insert(ht, id);
    }

    int Q;
    if (fscanf(f, "%d", &Q) != 1) {
        fprintf(stderr, "Failed to read Q (number of queries)\n");
        ht_free(ht);
        fclose(f);
        return 1;
    }

    /* store outputs in memory so we can compare them to the expected file */
    char **outputs = calloc((size_t)Q, sizeof(char*));
    if (!outputs && Q > 0) {
        fprintf(stderr, "Out of memory allocating outputs array\n");
        ht_free(ht);
        fclose(f);
        return 1;
    }

    for (int i = 0; i < Q; ++i) {
        int x;
        if (fscanf(f, "%d", &x) != 1) {
            fprintf(stderr, "Failed to read query %d\n", i);
            /* free what we have */
            for (int j = 0; j < i; ++j) free(outputs[j]);
            free(outputs);
            ht_free(ht);
            fclose(f);
            return 1;
        }
        if (ht_exists(ht, x))
            outputs[i] = strdup("YES");
        else
            outputs[i] = strdup("NO");
        if (!outputs[i]) {
            fprintf(stderr, "Out of memory storing output %d\n", i);
            for (int j = 0; j <= i; ++j) if (outputs[j]) free(outputs[j]);
            free(outputs);
            ht_free(ht);
            fclose(f);
            return 1;
        }
    }

    fclose(f);

    /* construct expected filename by inserting "-output" before extension if present */
    const char *inname = filename;
    const char *last_slash = strrchr(inname, '/');
    const char *last_back = strrchr(inname, '\\');
    const char *last_sep = last_slash > last_back ? last_slash : last_back;
    const char *last_dot = strrchr(inname, '.');

    char *expected_name;
    if (last_dot && (!last_sep || last_dot > last_sep)) {
        /* insert before last_dot */
        size_t prefix_len = (size_t)(last_dot - inname);
        size_t total = prefix_len + strlen("-output") + strlen(last_dot) + 1;
        expected_name = malloc(total);
        if (!expected_name) {
            fprintf(stderr, "Out of memory allocating expected filename\n");
            for (int j = 0; j < Q; ++j) free(outputs[j]);
            free(outputs);
            ht_free(ht);
            return 1;
        }
        memcpy(expected_name, inname, prefix_len);
        strcpy(expected_name + prefix_len, "-output");
        strcpy(expected_name + prefix_len + strlen("-output"), last_dot);
    } else {
        /* append to filename */
        size_t total = strlen(inname) + strlen("-output") + 1;
        expected_name = malloc(total);
        if (!expected_name) {
            fprintf(stderr, "Out of memory allocating expected filename\n");
            for (int j = 0; j < Q; ++j) free(outputs[j]);
            free(outputs);
            ht_free(ht);
            return 1;
        }
        strcpy(expected_name, inname);
        strcat(expected_name, "-output");
    }

    FILE *ef = fopen(expected_name, "r");
    if (!ef) {
        fprintf(stderr, "Expected output file '%s' not found\n", expected_name);
        /* print produced output to stdout so user can inspect */
        for (int i = 0; i < Q; ++i) {
            printf("%s\n", outputs[i]);
            free(outputs[i]);
        }
        free(outputs);
        free(expected_name);
        ht_free(ht);
        return 2;
    }

    /* compare line by line */
    char buf[1024];
    int mismatch = 0;
    for (int i = 0; i < Q; ++i) {
        if (!fgets(buf, sizeof(buf), ef)) {
            /* expected file has fewer lines */
            fprintf(stderr, "Mismatch: expected file ended early (expected at least %d lines)\n", Q);
            mismatch = 1;
            break;
        }
        /* trim newline and whitespace */
        size_t len = strlen(buf);
        while (len > 0 && (buf[len-1] == '\n' || buf[len-1] == '\r' || buf[len-1] == ' ' || buf[len-1] == '\t')) { buf[--len] = '\0'; }
        char *start = buf;
        while (*start == ' ' || *start == '\t') ++start;

        if (strcmp(start, outputs[i]) != 0) {
            fprintf(stderr, "Mismatch at line %d: got '%s' expected '%s'\n", i+1, outputs[i], start);
            mismatch = 1;
            break;
        }
    }

    /* check for extra lines in expected file */
    if (!mismatch) {
        if (fgets(buf, sizeof(buf), ef)) {
            /* there's extra content */
            fprintf(stderr, "Mismatch: expected file has more lines than produced output\n");
            mismatch = 1;
        }
    }

    if (!mismatch) {
        printf("Outputs match expected file '%s'\n", expected_name);
    }

    /* cleanup */
    for (int i = 0; i < Q; ++i) free(outputs[i]);
    free(outputs);
    fclose(ef);
    free(expected_name);
    ht_free(ht);
    return mismatch ? 1 : 0;
}

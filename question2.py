from typing import Dict, List, Sequence

def find_word_combos_with_pronunciation(phonemes: Sequence[str], pronunciation_dict: Dict[str, List[str]]) -> List[List[str]]:
    def dfs(remaining_phonemes, current_combination, result):
        if not remaining_phonemes:
            result.append(current_combination[:])
            return

        for word in pronunciation_dict:
            if remaining_phonemes[:len(pronunciation_dict[word])] == pronunciation_dict[word]:
                dfs(remaining_phonemes[len(pronunciation_dict[word]):], current_combination + [word], result)

    result = []
    dfs(phonemes, [], result)
    return result

pronunciation_dict = {
    "ABACUS": ["AE", "B", "AH", "K", "AH", "S"],
    "BOOK": ["B", "UH", "K"],
    "THEIR": ["DH", "EH", "R"],
    "THERE": ["DH", "EH", "R"],
    "TOMATO1": ["T", "AH", "M", "AH", "T", "OW"],
    "TOMATO2": ["T", "AH", "M", "EY", "T", "OW"],
}

result = find_word_combos_with_pronunciation(["DH", "EH", "R", "DH", "EH", "R"], pronunciation_dict)
print(result)

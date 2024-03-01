from typing import Sequence
import math


def prob_rain_more_than_n(p: Sequence[float], n: int) -> float:
    if n < 0 or n > len(p):
        raise ValueError("n must be between 0 to 365")

    total_days = len(p)
    successes = total_days - n

    prob_successes_or_more = 0
    for k in range(successes, total_days + 1):
        prob_k_successes = math.comb(total_days, k) * (p[0] ** k) * (1 - p[0]) ** (total_days - k)
        prob_successes_or_more += prob_k_successes

    return 1 - prob_successes_or_more

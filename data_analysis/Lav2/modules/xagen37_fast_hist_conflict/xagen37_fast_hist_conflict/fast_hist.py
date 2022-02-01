from typing import List, Tuple, Union
import numpy as np

def fast_hist(array: List[Union[int, float]], 
              bins: int) -> Tuple[List[int], List[float]]:
    """
    Builds bins' labels and bins' value counts for given array
    :param array: array with numeric values
    :param bins:  number of bins in result distribution
    :return: Two lists: 
             first contains value counts of each bin,
             second contains list of bins' labels
    """
    if (bins <= 0):
        raise ValueError("Number of bins must be positive")
    array = np.array(array)
    min_val = array.min()
    max_val = array.max()
    if (max_val == min_val):
        max_val += 0.1
        min_val -= 0.1
    step = (max_val - min_val) / bins     
    bins_ids = ((array - min_val) / step).astype(int)
    bins_ids[bins_ids == bins] -= 1
    bins_cnts = np.zeros(bins)
    uniques = np.unique(bins_ids, return_counts = True)
    bins_cnts[uniques[0]] += uniques[1]
    bins_names = np.linspace(min_val, max_val, num = bins + 1)
    return (bins_cnts, bins_names)
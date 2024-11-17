import torch
from laplace import Laplace

def apply_laplace(model, data_loader, likelihood='regression', prior_precision=1.0):
    """
    Applies the Laplace approximation to a trained neural network model.

    Args:
        model (torch.nn.Module): Trained neural network model.
        data_loader (torch.utils.data.DataLoader): DataLoader containing input data and targets.
        likelihood (str): Type of likelihood to use ('regression' or 'classification').
        prior_precision (float): Precision of the Gaussian prior on the weights.

    Returns:
        Laplace: Laplace object containing the posterior approximation.
    """
    # Initialize the Laplace approximation
    laplace = Laplace(model, likelihood=likelihood, prior_precision=prior_precision)

    # Collect all data points for fitting
    inputs, targets = [], []
    for data in data_loader:
        inputs.append(data[0])
        targets.append(data[1])

    inputs = torch.cat(inputs, dim=0)
    targets = torch.cat(targets, dim=0)

    # Fit the Laplace approximation
    laplace.fit(inputs, targets)

    return laplace


def extract_uncertainties(laplace, data_loader):
    """
    Extracts predictive uncertainties using the Laplace approximation.

    Args:
        laplace (Laplace): Laplace object containing the posterior approximation.
        data_loader (torch.utils.data.DataLoader): DataLoader with input data.

    Returns:
        tuple: Mean predictions and uncertainties for each input.
    """
    means, uncertainties = [], []
    for data in data_loader:
        inputs = data[0]
        pred_mean, pred_var = laplace(inputs, pred_type='glm')
        means.append(pred_mean.detach())
        uncertainties.append(pred_var.diagonal().detach())

    means = torch.cat(means, dim=0)
    uncertainties = torch.cat(uncertainties, dim=0)

    return means, uncertainties


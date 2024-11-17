import matplotlib.pyplot as plt
from sklearn.manifold import TSNE
import numpy as np

def visualize_latent_space(latent_points, uncertainties=None, labels=None, title="Latent Space Visualization"):
    """
    Visualizes the latent space with optional uncertainties and labels.

    Args:
        latent_points (numpy.ndarray): Array of latent points (2D or higher-dimensional).
        uncertainties (numpy.ndarray or None): Array of uncertainties corresponding to latent points (optional).
        labels (numpy.ndarray or None): Array of labels for coloring the points (optional).
        title (str): Title for the plot.
    """
    # Reduce dimensionality to 2D if needed
    if latent_points.shape[1] > 2:
        latent_points = TSNE(n_components=2).fit_transform(latent_points)

    plt.figure(figsize=(8, 6))
    scatter = plt.scatter(
        latent_points[:, 0], latent_points[:, 1],
        c=labels, cmap='viridis', alpha=0.8, edgecolor='k', s=50
    )
    if labels is not None:
        plt.colorbar(scatter, label='Labels')

    # Overlay uncertainties if provided
    if uncertainties is not None:
        uncertainties = np.array(uncertainties)
        plt.scatter(
            latent_points[:, 0], latent_points[:, 1],
            s=uncertainties * 100, alpha=0.4, edgecolor='red', facecolor='none', label="Uncertainty"
        )
        plt.legend()

    plt.title(title)
    plt.xlabel("Latent Dimension 1")
    plt.ylabel("Latent Dimension 2")
    plt.grid(True)
    plt.show()


def visualize_reconstruction(data, reconstruction, n_samples=10):
    """
    Visualizes original data and its reconstructions side by side.

    Args:
        data (numpy.ndarray): Original input data.
        reconstruction (numpy.ndarray): Reconstructed data.
        n_samples (int): Number of samples to visualize.
    """
    fig, axes = plt.subplots(2, n_samples, figsize=(15, 5))

    for i in range(n_samples):
        # Original data
        axes[0, i].imshow(data[i].reshape(28, 28), cmap='gray')
        axes[0, i].axis('off')
        axes[0, i].set_title("Original")

        # Reconstructed data
        axes[1, i].imshow(reconstruction[i].reshape(28, 28), cmap='gray')
        axes[1, i].axis('off')
        axes[1, i].set_title("Reconstruction")

    plt.tight_layout()
    plt.show()


import torch
import torch.nn as nn

import numpy as np
class DQN(nn.Module):
    def __init__(self,n_input,n_actions):
        super(DQN, self).__init__()
        self.network=nn.Sequential(
            nn.Linear(n_input,128),
            nn.ReLU(),
            nn.Linear(128,64),
            nn.ReLU(),
            nn.Linear(64,n_actions),
            nn.ReLU()
        )
    def forward(self,x):
        x=x.float()
        return self.network(x)
        






import torch
import torch.nn as nn
import numpy as np
class DQN(nn.Module):
    def __init__(self,n_input,n_actions):
        super(DQN, self).__init__()
        self.network=nn.Sequential(
            nn.Linear(n_input,400),
            nn.ReLU(),
            nn.Linear(400,400),
            nn.ReLU(),
            nn.Linear(400,n_actions)
        )
        self.value=nn.Sequential(
            nn.Linear(n_input,400),
            nn.ReLU(),
            nn.Linear(400,1)
            
            
            
            )
        
        
    def forward(self,x):
        x=x.float()
        adv=self.network(x)
        val=self.value(x)
        return val + (adv-adv.mean(dim=1, keepdim=True))
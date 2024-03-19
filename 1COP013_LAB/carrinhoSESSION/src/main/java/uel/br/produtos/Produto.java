package uel.br.produtos;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.NotNull;
import org.springframework.format.annotation.DateTimeFormat;

import java.io.Serializable;
import java.util.Date;
@Entity
public class Produto implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;
    @NotBlank(message = "O nome é obrigatório")
    private String nome;
    @NotNull(message = "O preco é obrigatório")
    private Double preco;
    @NotNull(message = "A quantidade é obrigatória")
    private Integer quantidade;
    public int getId() {
        return id;
    }
    public void setId(int id) {
        this.id = id;
    }
    public String getNome() {
        return nome;
    }
    public void setNome(String nome) {
        this.nome = nome;
    }
    public Double getPreco() { return preco; }
    public void setPreco(Double preco) { this.preco = preco; }
    public Integer getQuantidade() { return quantidade; }
    public void setQuantidade(Integer quantidade) { this.quantidade = quantidade; }
    @Override
    public boolean equals(Object o){
        if (o == null || this.getClass() != o.getClass()) {
            return false;
        }
        return ((Produto)o).id == (this.id);
    }
    @Override
    public int hashCode() {
        return id * 12345;
    }
}